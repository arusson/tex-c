#!/usr/bin/env python3

# Common between tangling and weaving.

import sys

COMMENTS = {
    'py': '#',
    'c': '//',
    'makefile': '#'
}
LANGUAGES = COMMENTS.keys()

def gobble_spaces(line, offset):
    '''
    Returns the offset of the next non blank character
    in the line starting from the value `offset`
    '''
    while offset < len(line) and line[offset] == ' ':
        offset += 1
    return offset

def parse_info(line, verb=False):
    '''
    Parses a fenced block info string.
    We expect only four possibilities:
    1. Nothing: returns None
    2. Only language: returns None
    3. Language followed by filename
    4. Language followed by block name << Name of the block >>
       with suffix '=' (optional) or '+='
    '''

    info = {
        'append': False,
        'fname': None,
        'bname': None
    }

    # First we strip the line and remove the backquotes,
    # then we find the offset of the next non blank character of this line
    # Stop here if there is nothing.
    line = line.strip()[3:]
    if len(line) == 0:
        return None
    offset = gobble_spaces(line, 0)

    # Parse language
    start = offset
    while offset < len(line) and line[offset] != ' ':
        offset += 1
    info['language'] = line[start:offset]
    if verb:
        print(f'[-] Language: {info["language"]}', file=sys.stderr)

    # We go to the next character.
    # If the end of line is reached, we ignore this info string.
    offset = gobble_spaces(line, offset)
    if offset == len(line):
        return None
    
    # We expect a filename or a descriptor that starts with `<<`.
    if line[offset:].startswith('<<'):
        # We look for the block name between the delimiters `<<` and `>>`
        # and strip the spaces at both ends.
        # If there is no end delimitor, then it's an error.
        found = False
        offset = gobble_spaces(line, offset + 2)
        start = offset
        last_nonblank = offset
        while offset < len(line) - 1:
            if line[offset:offset + 2] == '>>':
                found = True
                break
            if line[offset] != ' ':
                last_nonblank = offset
            offset += 1
        
        if not found and verb:
            # `fname` and `bname` both set to False in `info`.
            # It is considered an error so we return `info` as is.
            print('[!] Invalid block description.', file=sys.stderr)
            return None

        # We add the block name and look for a potential `+=`.        
        end = last_nonblank + 1
        offset += 2
        info['bname'] = line[start:end]
        offset = gobble_spaces(line, offset)
        if offset < len(line) - 1 and line[offset:offset + 2] == '+=':
            info['append'] = True

        if verb:
            if info['append']:
                print(f'[-] Block name: {info["bname"]}+=', file=sys.stderr)
            else:
                print(f'[-] Block name: {info["bname"]}', file=sys.stderr)
        return info

    # Last case: we consider the next characters to be a filename.
    # (No spaces allowed.)
    start = offset
    while offset < len(line) and line[offset] != ' ':
        offset += 1
    info['fname'] = line[start:offset]
    if verb:
        print(f'[-] Filename: {info["fname"]}', file=sys.stderr)
    return info

def get_fname_from_line(line, verb=False):
    '''
    Prerequisite: `line` is stripped.
    Cases:
      - `{{#include somefile.md}}`
      - `- [Some title](somefile.md)` with or without item `-`/`*`
      - None for any other cases
    Returns filename or None.
    '''

    # mdbook `{{#include somefile.md}}` is present.
    if line.startswith('{{#include ') and line.endswith('}}'):
        start = gobble_spaces(line, 11)
        end = start
        while end < len(line) - 2 and line[end] != ' ':
            end +=1
        return line[start:end]

    # Look for include with item `-`/`*`.
    if line.startswith('- ') or line.startswith('* '):
        # Now we expect `[Some stuff]`:
        # we look for the next non-space character.
        offset = gobble_spaces(line, 2)
        if line[offset] != '[':
            return None
        
        # We go to the closing brace.
        while offset < len(line) and line[offset] != ']':
            offset += 1
        if offset == len(line):
            if verb:
                print(f'[!] Closing "]" missing in line "{line}".', file=sys.stderr)
            return None
        
        # Remove potential spaces and look for '('.
        offset = gobble_spaces(line, offset + 1)
        if line[offset] != '(':
            return None

        start = gobble_spaces(line, offset + 1)
        end = start
        while end < len(line) - 1 and line[end] != ' ':
            end += 1
        
        # We have the filename, but we need to find the closing ')'.
        offset = gobble_spaces(line, end)
        if line[offset] == ')':
            return line[start:end]
        if verb:
            print(f'[!] Closing ")" missing in line "{line}".', file=sys.stderr)
    return None

def find_bname(line, comment, verb=False):
    '''
    We try to find ``<< ... >>'' in the line.
    If found, we return the starting position which is needed to indent
    each line of the block that will be inserted (if that block exists),
    and, of course, the name of the block that was found.
    '''

    # We find the starting position of the comment symbol.
    if comment not in line:
        return None
    i = line.index(comment)
    offset = i + len(comment)
    offset = gobble_spaces(line, offset)

    # If no opening `<<` we ignore this line.
    if not line[offset:].startswith('<<'):
        return None

    # Now we can look for the block name,
    # but we return None if there is no closing `>>`.
    found = False
    offset = gobble_spaces(line, offset + 2)
    start = offset
    last_nonblank = offset
    while offset < len(line) - 1:
        if line[offset:offset + 2] == '>>':
            found = True
            break
        if line[offset] != ' ':
            last_nonblank = offset
        offset += 1
    
    if not found:
        if verb:
            print(f'[!] Closing ">>" not found in code for line "{line}"', file=sys.stderr)
        return None
        
    end = last_nonblank + 1
    return i, line[start:end]
