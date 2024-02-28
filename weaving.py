#!/usr/bin/env python3

import os
import sys
from common import *

def find_part_from_section(num, part_starts):
    '''
    This function determines to which part a section belongs.
    Useful to create hyperlinks to pages.
    '''
    n = len(part_starts)
    if n == 1:
        return part_starts[0][1]
    mid = n // 2
    if num >= part_starts[mid][0]:
        return find_part_from_section(num, part_starts[mid:])
    return find_part_from_section(num, part_starts[:mid])

def add_header_bname(info, num, part_starts, verb=False):
    '''
    Add a block name on top of a block code.
    '''
    part = find_part_from_section(num, part_starts)
    bname = info['bname']
    # We replace "|variable|" by "*variable*"
    # Do nothing if there is an odd number of "|"
    n = bname.count('|')
    if n % 2 == 0:
        bname = bname.replace('|', '*')
    elif verb:
        print('[!] Odd numbers of "|" in block name.', file=sys.stderr)

    # Add the html tags with the div classes.
    title = f'⟨&nbsp;{bname} [{num}](./part{part:02d}.md#section-{num})&nbsp;⟩'
    if info['append']:
        title += '+'
    title += '≡\n'
    header = '<div class="blockcode">\n'       \
        '<div class="blockcode-header-bname">\n\n' \
        f'{title}</div>\n\n'
    return header

def add_header_fname(info):
    '''
    Same thing as the previous one, but for the filename.
    '''
    header = '<div class="blockcode">\n'       \
        '<div class="blockcode-header-fname">' \
        f'{os.path.basename(info["fname"])}</div>\n\n'
    return header

def add_footer_empty():
    return '</div>\n\n'

def add_footer_bname(block, part_starts):
    '''
    Add the footer for named blocks.
    There is the "This code is used in...", and "See also...".
    '''

    # "See also..." footer
    footer_seealso = '<div class="blockcode-footer-seealso">\n\n'
    block_def = block['def'][1:]
    if len(block_def) == 1:
        num = block_def[0]
        part = find_part_from_section(num, part_starts)
        footer_seealso += f'See also section [{num}](./part{part:02d}.md#section-{num}).'
    elif len(block_def) > 1:
        footer_seealso = '<div class="blockcode-footer-seealso">\n\n'
        footer_seealso += 'See also sections'
        for num in block_def[:-1]:
            part = find_part_from_section(num, part_starts)
            footer_seealso += f' [{num}](./part{part:02d}.md#section-{num}),'
        num = block_def[-1]
        part = find_part_from_section(num, part_starts)
        footer_seealso += f' and [{num}](./part{part:02d}.md#section-{num}).'
    
    footer = ''
    if len(block_def) > 0:
        footer += footer_seealso + '\n</div>'
    
    # "This is used in..." footer
    footer += '<div class="blockcode-footer-usedin">\n\n'
    block_used_in = block['used_in']
    if len(block_used_in) == 1:
        num = block_used_in[0]
        part = find_part_from_section(num, part_starts)
        footer += f'This code is used in section [{num}](./part{part:02d}.md#section-{num}).'
    else:
        footer += 'This code is used in sections'
        for num in block_used_in[:-1]:
            part = find_part_from_section(num, part_starts)
            footer += f' [{num}](./part{part:02d}.md#section-{num}),'
        num = block_used_in[-1]
        part = find_part_from_section(num, part_starts)
        footer += f' and [{num}](./part{part:02d}.md#section-{num}).'
    footer += '\n</div></div>\n\n'
    return footer

class Weaving:
    def __init__(self):
        self.NAMEBLOCKS = {}
        self.counter = 0
        self.level = -1
        self.cur_part = 0
        self.PART_STARTS = []
        
    def parse_file(self, fname):
        '''
        Expects one section per `#` title, so increment counter for each `#`.
        Returns False if an error occured.
        '''

        lines = open(fname, 'r').readlines()
        i = 0
        while i < len(lines):
            line = lines[i].strip()

            fname = get_fname_from_line(line)
            if fname is not None:
                self.level += 1
                res = self.parse_file(fname)
                if not res:
                    return False
                self.level -= 1

            # Increment counter only outside of main file.
            if line.startswith('# '):
                if self.level == -1:
                    # This is "# Summary".
                    self.level += 1
                # This is "# Part X".
                elif self.level == 0:
                    self.cur_part += 1
                    self.PART_STARTS.append((self.counter + 1, self.cur_part))
                else:
                    # This is a new section (outside of SUMMARY.md).
                    self.counter += 1
                i += 1
                continue

            # No code block, go to next line.
            if not line.startswith('```'):
                i += 1
                continue

            # Now we have a block
            info = parse_info(line)

            # Case 1: we don't care about this block.
            # We go through all lines until the closing "```".
            if info is None:
                found = False
                while i < len(lines) - 1:
                    i += 1
                    if lines[i].strip().startswith('```'):
                        found = True
                        break
                i += 1
                continue

            # Case 2: block name or filename is badly formatted.
            if info['bname'] is None and info['fname'] is None:
                return False

            # Case 3: we have a block to add.

            # We look for the language comment symbol(s).
            if info['language'] not in COMMENTS.keys():
                return False

            comment = COMMENTS[info['language']]

            # We have a block name and we note that it's defined
            # in this section (or a continuation of its definition).
            if info['bname'] is not None:
                if info['bname'] in self.NAMEBLOCKS.keys():
                    self.NAMEBLOCKS[info['bname']]['def'] += [self.counter]
                else:
                    self.NAMEBLOCKS[info['bname']] = {
                        'used_in': [],
                        'def': [self.counter]
                    }

            # Analyze all lines to find block names.
            found = False
            while i < len(lines) - 1:
                i += 1
                line = lines[i]
                res = find_bname(line, comment)
                # Add the section reference if the line is a block name.
                if res is not None:
                    _, bname = res
                    if bname in self.NAMEBLOCKS.keys():
                        self.NAMEBLOCKS[bname]['used_in'] += [self.counter]
                    else:
                        self.NAMEBLOCKS[bname] = {
                            'used_in': [self.counter],
                            'def': []
                        }
                # Stop analyzing if block ends.
                if line.strip().startswith('```'):
                    found = True
                    break
            
            # Goto next line and continue loop.
            i += 1
        return True

    def modify_book(self, book, verb=False):
        '''
        Thus function modifies the book parsed by mdBook.
        This is where we add the HTML tags to add headers and footers,
        but also the "NOTE" blocks.
        '''

        self.counter = 0
        sections = book['sections']
        for section in sections:
            if not 'Chapter' in section.keys():
                continue

            # Run through lines to add header and footer
            # for each block using info parsed with `parse_file` method

            lines = section['Chapter']['content'].split('\n')
            i = 0
            content = ''
            while i < len(lines):
                line = lines[i]
                line_strip = line.strip()

                if line_strip.startswith('# '):
                    self.counter += 1
                    content += line + '\n'
                    i += 1
                    continue


                # Blockquote for a NOTE.
                if line.startswith('> ![NOTE]'):
                    # Add header with "NOTE".
                    content += '<div class="blocknote">\n' \
                        '<div class="blocknote-header">NOTE</div>\n\n'
                    i += 1
                    while i < len(lines):
                        line_strip = lines[i].strip();
                        if line_strip.startswith('> ') or line_strip == '>':
                            content += lines[i] + '\n'
                            i += 1
                        else:
                            break
                    # add closing </div>
                    content += '</div>\n\n'
                    continue


                if not line_strip.startswith('```'):
                    content += line + '\n'
                    i += 1
                    continue

                info = parse_info(line_strip)

                # Case 1: we don't care about this block.
                if info is None:
                    content += line + '\n'
                    found = False
                    while i < len(lines) - 1:
                        i += 1
                        content += lines[i] + '\n'
                        if lines[i].strip().startswith('```'):
                            found = True
                            break
                    i += 1
                    continue

                # Case 2: block name or filename badly formatted.
                if info['bname'] is None and info['fname'] is None:
                    return None
                
                # Case 3: there is a block.
                if info['language'] not in COMMENTS.keys():
                    return None
                
                if info['bname'] is not None:
                    content += add_header_bname(info, self.NAMEBLOCKS[info['bname']]['def'][0], self.PART_STARTS, verb)
                else:
                    content += add_header_fname(info)
                
                # We add the "```" with only language because it breaks mdBook
                # rendering in some cases with the block names in info string.
                content += f'```{info["language"]}\n'

                # Add all lines of the block.
                found = False
                while i < len(lines) - 1:
                    i += 1
                    # We check if the line is a block name, then we add
                    # the section number (calculated during the parsing).

                    res = find_bname(lines[i], COMMENTS[info['language']], verb)
                    if res is None:
                        content += lines[i] + '\n'
                    else:
                        # There is a named block referenced
                        # and we add its section number
                        indent, bname = res
                        num = self.NAMEBLOCKS[bname]['def'][0]
                        line = ' '*indent + COMMENTS[info['language']] + f' << {bname}, {num} >>\n'                        
                        content += line

                    if lines[i].strip().startswith('```'):
                        found = True
                        break
                
                # Add footer.
                if info['bname'] is not None and not info['append']:
                    content += add_footer_bname(self.NAMEBLOCKS[info['bname']], self.PART_STARTS)
                else:
                    content += add_footer_empty()
                
                # Goto next line and continue loop.
                i += 1
            
            # End of this chapter: we replace its content.
            section['Chapter']['content'] = content
        return book
