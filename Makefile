
run : ./main out.txt

out.txt : in.txt ./main
	cat $< | ./main > $@ 2> err.txt
