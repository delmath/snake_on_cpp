TARGET = snake.exe
CXX = g++
SRCDIR = src
OBJDIR = obj

SOURCES = 	$(SRCDIR)/main.cpp	\
			$(SRCDIR)/menu.cpp	\
			$(SRCDIR)/game.cpp	\
			$(SRCDIR)/save.cpp	\
#			$(SRCDIR)/multi-game.###cpp	\
#			$(SRCDIR)/snake.cpp	\
#			$(SRCDIR)/fruit.cpp	\

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ -lws2_32

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) -c -o $@ $< -MMD -MF $(@:.o=.d) -I includes/

-include $(OBJDIR)/*.d

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	del /Q /F $(TARGET)
	rmdir /S /Q $(OBJDIR)

re: clean all

.PHONY: all clean