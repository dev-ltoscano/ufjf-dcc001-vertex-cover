CP = g++
LK = g++
FLAGS = -O3 -std=c++11 -Wno-unused-result

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj

OBJ = $(OBJ_DIR)/GraphEdge.o $(OBJ_DIR)/GraphVertex.o $(OBJ_DIR)/Graph.o $(OBJ_DIR)/SATVertexCover.o $(OBJ_DIR)/main.o
APP = SATVertexCover

all: before $(OBJ)
	$(LK) -o $(APP) $(OBJ)
	
before:
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/GraphEdge.o: $(SRC_DIR)/GraphEdge.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/GraphEdge.cpp -o $(OBJ_DIR)/GraphEdge.o
	
$(OBJ_DIR)/GraphVertex.o: $(SRC_DIR)/GraphVertex.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/GraphVertex.cpp -o $(OBJ_DIR)/GraphVertex.o
	
$(OBJ_DIR)/Graph.o: $(SRC_DIR)/Graph.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/Graph.cpp -o $(OBJ_DIR)/Graph.o
	
$(OBJ_DIR)/SATVertexCover.o: $(SRC_DIR)/SATVertexCover.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/SATVertexCover.cpp -o $(OBJ_DIR)/SATVertexCover.o
	
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

clean: 
	rm -f $(APP) $(OBJ)
	rm -rf $(OBJ_DIR)
