CP = g++
LK = g++
FLAGS = -O2 -std=c++11

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj

OBJ = $(OBJ_DIR)/GraphEdge.o $(OBJ_DIR)/GraphVertex.o $(OBJ_DIR)/Graph.o $(OBJ_DIR)/MergeSort.o $(OBJ_DIR)/VertexCover.o $(OBJ_DIR)/main.o
APP = VertexCover

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
	
$(OBJ_DIR)/MergeSort.o: $(SRC_DIR)/MergeSort.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/MergeSort.cpp -o $(OBJ_DIR)/MergeSort.o
	
$(OBJ_DIR)/VertexCover.o: $(SRC_DIR)/VertexCover.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/VertexCover.cpp -o $(OBJ_DIR)/VertexCover.o
	
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CP) $(FLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

clean: 
	rm -f $(APP) $(OBJ)
	rm -rf $(OBJ_DIR)