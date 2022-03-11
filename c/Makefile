cc = gcc

fibonacci_tree: fibonacci_tree.c
	clang-format -i fibonacci_tree.c
	$(cc) -o $@ $^

clean:
	rm fibonacci_tree fibonacci_tree.dot

