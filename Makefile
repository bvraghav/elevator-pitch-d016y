OBJ		:= dist/obj
BIN		:= dist/bin
RUN		:= dist/run
SRC		:= src

CXXFLAGS	:= -I $(SRC)
# CXXFLAGS	:= -I $(SRC) -static
# LDLIBS	:= -Wl,-Bstatic -L$(OBJ)
# LDFLAGS	:= 
ARFLAGS		:= rcs

run : $(BIN) $(BIN)/main $(RUN)/out.txt

$(RUN)/out.txt : $(RUN)/in.txt $(BIN)/main $(RUN)
	cat $< | ./$(BIN)/main > $@ 2> $(RUN)/err.txt

$(RUN)/in.txt : ./sample.in.txt $(RUN)
	cp $< $@

$(OBJ)/%.o : $(SRC)/bvr/%.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(OBJ)/lib%.a : $(OBJ)/%.o
# 	$(AR) $(ARFLAGS) $(@) $(^)


# mainSrc_	:= $(SRC)/bvr/main.cpp
# mainDeps_	+= $(SRC)/bvr/debug.cpp
# mainDeps_	+= $(SRC)/bvr/input.cpp
# mainDeps_	+= $(SRC)/bvr/signal.cpp
# mainDeps_	+= $(SRC)/bvr/elevator.cpp

mainSrc_	:= $(OBJ)/main.o
mainDeps_	+= $(OBJ)/debug.o
mainDeps_	+= $(OBJ)/input.o
mainDeps_	+= $(OBJ)/signal.o
mainDeps_	+= $(OBJ)/elevator.o
mainDeps_	+= $(OBJ)/coroutine.o
# mainLibs_ 	+= $(OBJ)/libmain.a
$(BIN)/main :   $(mainSrc_) $(mainDeps_) | $(mainLibs_)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o $(@) $(^) \
	  $(mainLibs_:$(OBJ)/lib%.a=-l%)

# $(OBJ)/libmain.a : $(mainSrc_) $(mainDeps_)
# 	$(AR) $(ARFLAGS) $(@) $(^)

scratch : $(BIN)/scratch $(RUN)/scratchOut.txt

$(RUN)/scratchOut.txt : $(BIN)/scratch
	cat $< | $(BIN)/scratch > $@ 2> $(RUN)/scratchErr.txt

scratchSrc_	:= $(SRC)/bvr/scratch.cpp
$(BIN)/scratch :   $(scratchSrc_) 
	$(CXX) -o $(@) $(^) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)




$(RUN) $(BIN) $(OBJ) :
	mkdir -p $(@)
