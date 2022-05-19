cc = gcc

fibonacci_tree: fibonacci_tree.c
	clang-format -i fibonacci_tree.c
	$(cc) -o $@ $^

.PHONY: maze course_list

serial2dot: serial2dot.c
	$(cc) -o $@ $^

maze:
	clang-format -i maze.c
	$(cc) -o maze maze.c

mazeO2:
	clang-format -i maze.c
	$(cc) -O2 -o maze maze.c

course_list:
	clang-format -i course_list.c
	$(cc) -o course_list course_list.c
	./course_list < course_list_input.txt

clean:
	-rm fibonacci_tree fibonacci_tree.dot
	-rm maze
	-rm course_list
	-rm serial2dot serialBST.dot
