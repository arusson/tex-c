#!/usr/bin/env python3

import os
import sys
from common import *

def prepare_line(line, cur_indent, language):
    '''
    If language is C, no indentation for labels except for switch cases.
    Same for "#ifdef" and "#endif"
    '''
    if language == 'c':
        line_strip = line.strip()
        if line_strip.startswith('#ifdef') or line_strip.startswith('#endif'):
            return line_strip + '\n'
        
        # A few other cases where we keep the indentation
        if line_strip.endswith(':') \
            and not line_strip.startswith('//') \
            and not line_strip.startswith('case') \
            and not line_strip.startswith('non_math') \
            and not line_strip.startswith('any_mode') \
            and not line_strip.startswith('add_delims_to') \
            and not line_strip.startswith('any_state_plus') \
            and not line_strip.endswith('// =:') \
            and line_strip != 'default:':
            return line_strip + '\n'
    return cur_indent*' ' + line + '\n'

class Tangling:
    def __init__(self):
        self.BLOCKS = {}
        self.FILES = {}
        self.counter = 0
        self.level = 0

    def parse_file(self, fname, verb=False):
        '''
        Expects one section per `#` title, so increment counter for each `#`.
        Returns False if an error occured.
        '''

        lines = open(fname, 'r').readlines()
        i = 0
        while i < len(lines):
            line = lines[i].strip()

            fname = get_fname_from_line(line, verb)
            if fname is not None:
                self.level += 1
                res = self.parse_file(fname, verb)
                if not res:
                    return False
                self.level -= 1

            # Increment counter only outside of main file.
            if line.startswith('#') and self.level > 0:
                self.counter += 1

            # No code block, go to next line.
            if not line.startswith('```'):
                i += 1
                continue

            # Now we have a block.
            info = parse_info(line, verb)

            # Case 1: we don't care about this block.
            # We go through all lines until the closing "```".
            if info is None:
                found = False
                while i < len(lines) - 1:
                    i += 1
                    if lines[i].strip().startswith('```'):
                        found = True
                        break
                if not found and verb:
                    print('[!] Closing "```" not found for non contributing block.')
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

            if verb:
                print(f'[x] Section {self.counter}')

            # Section header
            if info['bname'] is not None and not info['append']:
                block = f'{comment} ~~~ {info["bname"]}, {self.counter} ~~~\n'
            elif info['fname'] in self.FILES.keys():
                block = f'\n{comment} ~~~ Section {self.counter} ~~~\n'
            else:
                # If new file, do not add an empty line.
                block = f'{comment} ~~~ Section {self.counter} ~~~\n'

            # Add all lines of the block.
            found = False
            while i < len(lines) - 1:
                i += 1
                line = lines[i]
                if line.strip().startswith('```'):
                    found = True
                    break
                block += line
            if not found and verb:
                print('[!] Closing "```" not found, EOF considered as "```".')
            
            # Section ending
            if info['fname'] != None:
                block += f'{comment} ~~~ End section {self.counter} ~~~\n'
                # If file already exists, we append the block,
                # otherwise we create a new file.
                if info['fname'] in self.FILES.keys():
                    if verb:
                        print('[-] This file exists.')
                    self.FILES[info['fname']]['content'] += block
                else:
                    if verb:
                        print('[-] This is a new file.')
                    self.FILES[info['fname']] = {
                        'language': info['language'],
                        'content': block
                    }
            else:
                if info['append']:
                    block += f'{comment} ~~~ End section {self.counter} ~~~\n'
                    if verb:
                        print('[-] Block appended.')
                    if info['bname'] in self.BLOCKS.keys():
                        self.BLOCKS[info['bname']]['content'] += '\n' + block
                    else:
                        print('You cannot have a "+=" block if it has not be defined first.')
                        return False
                else:
                    if info['bname'] in self.BLOCKS.keys():
                        print('This block already exists!')
                        return False
                    if verb:
                        print('[-] New block created')
                    self.BLOCKS[info['bname']] = {'counter': self.counter, 'content': block}
            # Goto next line and continue loop
            i += 1
        return True
        
    def add_block(self, block, content, cur_indent, language, verb=False):
        '''
        Add `block` to `content` string.
        `cur_indent` is the identation of this block.
        If a named block appears on a line of this block,
        then this method is called recursively.
        '''
        comment = COMMENTS[language]
        lines = block.split('\n')
        for line in lines[:-1]:
            res = find_bname(line, comment, verb)
            # No block name, we add the line
            if res is None:
                content += prepare_line(line, cur_indent, language)
                continue

            # Add the named block if it exists, or just add the line.
            indent, bname = res
            if bname in self.BLOCKS.keys():
                inner_block = self.BLOCKS[bname]['content']
                content = self.add_block(inner_block, content, cur_indent + indent, language, verb)
                content += (cur_indent + indent)*' ' + f'{comment} ~~~ End section {self.BLOCKS[bname]["counter"]} ~~~\n'
            else:
                content += cur_indent*' ' + line + '\n'
        return content

    def build_files(self, dir, verb=False):
        '''
        Create the files.
        Each file is treated as a block, so the method `add_block` is called.
        '''
        if not dir.endswith('/'):
            dir += '/'
        for fname in self.FILES:
            if verb:
                print(f'[-] Building file {fname}')
            dirpath = os.path.dirname(dir + fname)
            if len(dirpath) > 0:
                os.makedirs(dirpath, exist_ok=True)
            f = open(dir + fname, 'w')
            block = self.FILES[fname]['content']
            language = self.FILES[fname]['language']
            content = self.add_block(block, '', 0, language, verb)
            f.write(content)
            f.close()

def print_usage():
    print('Usage:')
    print('  python3 lit.py [-v] <MAIN_FILE.md> <OUTPUT FOLDER>')

if __name__ == "__main__":
    argc = len(sys.argv)

    # Parsing of arguments
    main_file_set = False
    output_folder_set = False
    verb = False
    
    i = 1
    while i < argc:
        arg = sys.argv[i]
        if arg == '-v':
            if verb:
                print('Two much of `-v`!')
                print_usage()
                sys.exit()
            else:
                verb = True
        elif not main_file_set:
            main_file = arg
            main_file_set = True
        elif not output_folder_set:
            output_folder = arg
            output_folder_set = True
        else:
            print('Too many arguments!')
            print_usage()
            sys.exit()
        i += 1

    if not (main_file_set and output_folder_set):
        print('You forgot arguments.')
        print_usage()
        sys.exit()

    # We go into the directory while parsing files.
    old_path = os.getcwd()
    path = os.path.dirname(main_file)
    os.chdir(path)
    main_file = os.path.basename(main_file)
    
    if verb:
        print(f'[-] Main file: {main_file}')
        print(f'[-] Output folder: {output_folder}')
    tangler = Tangling()
    tangler.parse_file(main_file, verb)

    # We go back to old path and build files.
    os.chdir(old_path)
    print('current:', os.getcwd())
    tangler.build_files(output_folder, verb)
