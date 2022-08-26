
oldawk=${oldawk-awk}
awk=${awk-../a.out}

echo oldawk=$oldawk, awk=$awk

for i
do
	echo "$i:"
	$oldawk -f $i test.countries test.countries >old.output
	$awk -f $i test.countries test.countries >awk.output
	if cmp -s old.output awk.output
	then true
	else echo "$i:	BAD ..."
	fi
	diff  -u -b old.output awk.output | sed -e 's/^/	/' -e 10q
done
