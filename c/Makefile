cc = gcc

fibonacci_tree: fibonacci_tree.c
	clang-format -i fibonacci_tree.c
	$(cc) -o $@ $^

maze: maze.c
	clang-format -i maze.c
	$(cc) -o $@ $^

clean:
	rm fibonacci_tree fibonacci_tree.dot
	rm maze
