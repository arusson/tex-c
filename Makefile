.PHONY: tangling weaving virtex initex triptex trip clean

tangling:
	python3 tangling.py -v src/SUMMARY.md code

weaving:
	mdbook build

virtex:
	make -C code virtex

initex:
	make -C code initex

triptex:
	make -C code triptex

trip: triptex
	mv code/bin/triptex trip/
	make -C trip

clean:
	make -C code clean
	make -C trip clean
