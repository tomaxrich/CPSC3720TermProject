CXX_9=g++9.1
CXX=g++
CXXFLAGS= -g -fprofile-arcs -ftest-coverage
CXXFLAGS_TEST = -std=c++11 -g -fprofile-arcs -ftest-coverage

LINKFLAGS = -lrestbed -lpthread
LINKFLAGS_TEST = -lgtest
LINKFLAGS_REST = /usr/local/lib/librestbed.a -lpthread

SRC_DIR_MAIN_SERVER = src/server/main.cpp
SRC_DIR_MAIN_CLIENT = src/client/main.cpp
SRC_DIR_SERVER = src/server/src
SRC_DIR_CLIENT = src/client/src
# Old SRC_DIR_CLIENT = src/client
#SRC_DIR_SERVICE = src/service
SRC_DIR_SERVICE_TEST = src/server/src

TEST_DIR = test

SERVICE_INCLUDE = -I include/service
SERVICE_INCLUDE_TEST = -I src/server/include
SERVER_INCLUDE = -I src/server/include
CLIENT_INCLUDE = -I src/client/include

SERVER_INCLUDE_NO_I = src/server/include
CLIENT_INCLUDE_NO_I = src/client/include


GCOV_9 = gcov9.1
GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint.py

PROGRAM_SERVER = issueServer
PROGRAM_CLIENT = issueClient
PROGRAM_TEST = issueTest
PROGRAM_SERVER_LOCAL = localServer
PROGRAM_CLIENT_LOCAL = localClient

.PHONY: all
all: $(PROGRAM_SERVER) $(PROGRAM_CLIENT) $(PROGRAM_TEST) coverage docs static style

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \
	$(COVERAGE_RESULTS) \
	$(PROGRAM_SERVER) \
	$(PROGRAM_SERVER_LOCAL) \
	$(PROGRAM_TEST) \
	$(PROGRAM_TEST_LOCAL) \
	$(PROGRAM_CLIENT) \
	$(PROGRAM_CLIENT_LOCAL) \
	$(COVERAGE_DIR) \
	doxygen/html \
	obj bin \

server: $(PROGRAM_SERVER)

server-local: $(PROGRAM_SERVER_LOCAL)

client: $(PROGRAM_CLIENT)

client-local: $(PROGRAM_CLIENT_LOCAL)

runServer: server
	./${PROGRAM_SERVER} &

stopServer:
	kill -9 ${PROGRAM_SERVER}

#old make calls
#$(PROGRAM_SERVER): $(SRC_DIR_SERVER) $(SRC_DIR_SERVICE)
#	$(CXX_9) $(CXXFLAGS) -o $(PROGRAM_SERVER) $(SERVICE_INCLUDE) \
#	$(SERVER_INCLUDE) $(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_SERVICE)/*.cpp $(LINKFLAGS)
	
$(PROGRAM_SERVER): $(SRC_DIR_SERVER)
	$(CXX_9) $(CXXFLAGS) -o $(PROGRAM_SERVER) \
	$(SERVER_INCLUDE) $(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_MAIN_SERVER) \
	$(LINKFLAGS)

#$(PROGRAM_SERVER_LOCAL): $(SRC_DIR_SERVER) $(SRC_DIR_SERVICE)
#	$(CXX) $(CXXFLAGS) -o $(PROGRAM_SERVER_LOCAL) $(SERVICE_INCLUDE) \
#	$(SERVER_INCLUDE) $(SRC_DIR_SERVER)/*.cpp \
#	$(SRC_DIR_SERVICE)/*.cpp $(LINKFLAGS_REST)

$(PROGRAM_SERVER_LOCAL): $(SRC_DIR_SERVER)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_SERVER_LOCAL) \
	$(SERVER_INCLUDE) $(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_MAIN_SERVER) \
	$(LINKFLAGS_REST)

#old make calls
#$(PROGRAM_CLIENT): $(SRC_DIR_CLIENT)
#	$(CXX_9) $(CXXFLAGS) -o $(PROGRAM_CLIENT) \
#	$(SRC_DIR_CLIENT)/*.cpp $(LINKFLAGS)

$(PROGRAM_CLIENT): $(SRC_DIR_CLIENT)
	$(CXX_9) $(CXXFLAGS) -o $(PROGRAM_CLIENT) $(CLIENT_INCLUDE) \
	$(SRC_DIR_CLIENT)/*.cpp $(SRC_DIR_MAIN_CLIENT) $(LINKFLAGS)


#$(PROGRAM_CLIENT_LOCAL): $(SRC_DIR_CLIENT)
#	$(CXX) $(CXXFLAGS) -o $(PROGRAM_CLIENT_LOCAL) \
#	$(SRC_DIR_CLIENT)/*.cpp $(LINKFLAGS_REST)

$(PROGRAM_CLIENT_LOCAL): $(SRC_DIR_CLIENT)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_CLIENT_LOCAL) $(CLIENT_INCLUDE) \
	$(SRC_DIR_CLIENT)/*.cpp $(SRC_DIR_MAIN_CLIENT) $(LINKFLAGS_REST)

#$(PROGRAM_TEST): $(TEST_DIR) $(SRC_DIR_SERVICE)
#	$(CXX) $(CXXFLAGS) -o ./$(PROGRAM_TEST) $(SERVICE_INCLUDE) \
#	$(TEST_DIR)/*.cpp $(SRC_DIR_SERVICE)/*.cpp $(LINKFLAGS_TEST)

$(PROGRAM_TEST): $(TEST_DIR)
	$(CXX) $(CXXFLAGS_TEST) -o ./$(PROGRAM_TEST) \
	$(TEST_DIR)/*.cpp $(LINKFLAGS_TEST)

#$(PROGRAM_TEST): $(TEST_DIR) $(SRC_DIR_SERVICE_TEST)
#	$(CXX) $(CXXFLAGS) -o ./$(PROGRAM_TEST) $(CLIENT_INCLUDE) $(SERVICE_INCLUDE) \
#	$(TEST_DIR)/*.cpp $(SRC_DIR_SERVICE)/*.cpp $(LINKFLAGS_TEST)

tests: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)

memcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes ./$(PROGRAM_TEST)

coverage: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)
	$(PROGRAM_TEST)
	# Determine code coverage
	$(GCOV) -b $(SRC_DIR_SERVICE)/*.cpp -o .
	#Remove all of the generated files from gcov
	rm -f *.gc*

static: ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE} ${TEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR_SERVER} ${SRC_DIR_CLIENT} ${SRC_DIR_SERVICE} ${TEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

#style:  ${SRC_INCLUDE}
#	${STYLE_CHECK} $(SERVER_INCLUDE_NO_I)/*.h $(CLIENT_INCLUDE_NO_I)/*.h $(SRC_DIR_CLIENT)/*.cpp \
#	$(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_MAIN_SERVER) $(SRC_DIR_MAIN_CLIENT)

style:  ${SERVER_INCLUDE_NO_I} ${CLIENT_INCLUDE_NO_I}
	${STYLE_CHECK} $(SERVER_INCLUDE_NO_I)/*.h $(CLIENT_INCLUDE_NO_I)/*.h $(SRC_DIR_CLIENT)/*.cpp \
	$(SRC_DIR_SERVER)/*.cpp $(SRC_DIR_MAIN_SERVER) $(SRC_DIR_MAIN_CLIENT)

docs:
	doxygen doxygen/doxyfile
