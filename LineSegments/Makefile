# Define the target executable name
TARGET = i
TARGET2 = linesegment_linux.out
TARGET3 = eq
TARGETPLOT1 = plot1
TARGETSUB = sub

# Define the source file name
SRC = soln.cpp
SRCSUB = 22B0963.cpp
SRCPLOTS = plots.cpp
SRC3 = soln.cpp

# Specify the compiler and compiler flags
CXX = g++

# Default rule to compile the source file into the target executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX)	-o	$@	$^

eq: $(TARGET3)

$(TARGET3): $(SRC3)
	$(CXX)	-o	$@	$^

# plots_compile: $(TARGETPLOT1) 

# $(TARGETPLOT1): $(SRCPLOTS)
# 	$(CXX)	-o	$@	$^
# Rule to process input files using the executable
process_input_files: $(TARGET)
	mkdir -p my_outputs; \
	for input_file in input*.txt; do \
		output_file=my_outputs/$$(echo $$input_file | sed 's/input/o/'); \
		echo "Processing $$input_file"; \
		./$(TARGET) < $$input_file > $$output_file; \
	done

process_input_files_2: $(TARGET2)
	mkdir -p their_outputs; \
	for input_file in input*.txt; do \
		output_file=their_outputs/$$(echo $$input_file | sed 's/input/o/'); \
		echo "Processing $$input_file"; \
		./$(TARGET2) < $$input_file > $$output_file; \
	done

process_input_files_3: $(TARGET3)
	mkdir -p eq_outputs; \
	for input_file in input*.txt; do \
		output_file=eq_outputs/$$(echo $$input_file | sed 's/input/o/'); \
		echo "Processing $$input_file"; \
		./$(TARGET3) < $$input_file > $$output_file; \
	done

plots:$(TARGETPLOT1) 

$(TARGETPLOT1): $(SRCPLOTS)
	$(CXX)	-o	$@	$^
	mkdir -p plots; 
	for input_file in input*.txt; do \
		output_file=plots/$$(echo $$input_file | sed 's/input/my_outline/'); \
		echo "Processing $$input_file"; \
		./$(TARGETPLOT1) < $$input_file > $$output_file; \
	done

sub:$(TARGETSUB) 

$(TARGETSUB): $(SRCSUB)
	$(CXX)	-o	$@	$^
	mkdir -p subout; 
	for input_file in input*.txt; do \
		output_file=subout/$$(echo $$input_file | sed 's/input/subo/'); \
		echo "Processing $$input_file"; \
		./$(TARGETSUB) < $$input_file > $$output_file; \
	done
# Clean rule to remove the target executable
clean:
	rm	-f	$(TARGET)
