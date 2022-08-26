
oldawk=${oldawk-myawk}
awk=${awk-../a.out}

echo oldawk=$oldawk, awk=$awk

for i
do
	echo "$i:"
	$oldawk -f $i test.data >old.output
	$awk -f $i test.data >awk.output
	if cmp -s old.output awk.output
	then true
	else echo "$i:	BAD ..."
	fi
	diff  -u -b old.output awk.output | sed -e 's/^/	/' -e 10q
done
