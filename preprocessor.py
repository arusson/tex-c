import os
import json
import sys
from weaving import Weaving

if __name__ == '__main__':
    if len(sys.argv) > 1: # we check if we received any argument
        if sys.argv[1] == "supports": 
            # then we are good to return an exit status code of 0, since the other argument will just be the renderer's name
            sys.exit(0)

    # load both the context and the book representations from stdin
    context, book = json.load(sys.stdin)
    
    # and now, we can just modify the content
    old_book = book.copy()
    old_path = os.getcwd()
    os.chdir('src')
    weaver = Weaving()
    weaver.parse_file('SUMMARY.md')
    book = weaver.modify_book(book, verb=True)
    os.chdir('..')

    # we are done with the book's modification, we can just print it to stdout, 
    if book is None:
        print(json.dumps(old_book))
    else:
        print(json.dumps(book))
