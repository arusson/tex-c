.PHONY: clean trip

trip:
	printf '\n\\input trip' | ./triptex >/dev/null
	diff -y --suppress-common-lines trip.log master/tripin.log > tripin_log.diff || true
	printf ' &trip  trip ' | ./triptex > trip.fot
	diff -y --suppress-common-lines trip.log master/trip.log > trip_log.diff || true
	cp TeXfonts/trip.tfm ./
	dvitype -dpi=72.27 -output-level=2 -page-start="*.*.*.*.*.*.*.*.*.*" trip.dvi > trip.typ
	diff -y --suppress-common-lines trip.typ master/trip.typ > trip_typ.diff || true

clean:
	rm -f trip.{dvi,fmt,fot,log,typ,tfm} tripos.tex *.diff 8terminal.tex triptex
