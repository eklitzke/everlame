everlame: everlame.cc
	@echo "compilin dat prog"
	@$(CXX) -O3 -std=c++11 -flto -pedantic -Wall $^ -o $@
	@echo "optimizin dat prog"
	@strip -s $@   # for extra speed lol

.PHONY: test
test: everlame
	@echo -e 'Qa   Zj\nMZca\n\nKhfa' | ./everlame


.PHONY: clean
clean:
	@echo "cleanin dat prog"
	@rm -f everlame
