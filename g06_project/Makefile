.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base
TARGETANALYSIS = cs296_base_analysis
INSTALL = install

# Project Paths
PROJECT_ROOT=$(HOME)/g06_project/
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src/
SRCDIRANALYSIS = $(PROJECT_ROOT)/src/analysis
OBJDIR = $(PROJECT_ROOT)/obj
OBJDIRANALYSIS = $(PROJECT_ROOT)/objanalysis
BINDIR = $(PROJECT_ROOT)/bin
BINDIRANALYSIS = $(PROJECT_ROOT)/binanalysis
DOCDIR = $(PROJECT_ROOT)/doc

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS_debug = -g -Wall
CPPFLAGS_release = -g -O3 -Wall
CPPFLAGS_debug+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
CPPFLAGS_release+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
CPPFLAGS =-g -O3 -Wall 
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
SRCSANALYSIS := $(wildcard $(SRCDIRANALYSIS)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJSANALYSIS := $(SRCSANALYSIS:$(SRCDIRANALYSIS)/%.cpp=$(OBJDIRANALYSIS)/%.o)

.PHONY: all setup doc clean distclean

all: setup $(BINDIR)/$(TARGET)

analysis: setup $(BINDIR)/$(TARGETANALYSIS)

exe_debug: setup $(OBJSANALYSIS)
	@g++ -o $(BINDIR)/$(TARGETANALYSIS) $(CPPFLAGS_debug) $(LDFLAGS) $(OBJSANALYSIS) $(LIBS) -MD -pg

exe_release: setup $(OBJSANALYSIS)
	@g++ -o $(BINDIR)/$(TARGETANALYSIS) $(CPPFLAGS_release) $(LDFLAGS) $(OBJSANALYSIS) $(LIBS) -MD -pg

setup:
	@mkdir -p obj
	@mkdir -p bin
	@mkdir -p objanalysis
	@mkdir -p data plots

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

$(BINDIR)/$(TARGETANALYSIS): $(OBJSANALYSIS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJSANALYSIS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include -include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

$(OBJSANALYSIS): $(OBJDIRANALYSIS)/%.o : $(SRCDIRANALYSIS)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

plot02: analysis
	@mkdir -p data plots
	@cd scripts; \
	python g06_gen_csv.py; \
	python g06_gen_plots.py;
	@cd data; \
	rm -f avg_rerun.csv avg_iteration.csv avg_deviation.csv freq.csv

plot01:
	@mkdir -p data plots
	@cd scripts; \
	./gen_data.sh; \
	./gen_csv.sh; \
	./avg-iteration.sh; \
	./avg-rerun.sh; \
	./avg-iteration.sh; \
	./avg-deviation.sh; \
	./freq.sh; \
	./avg-iteration.sh
	@gnuplot 'scripts/g06_plot01.gpt'
	@gnuplot 'scripts/g06_plot02.gpt'
	@gnuplot 'scripts/g06_plot03.gpt'
	@gnuplot 'scripts/g06_plot04.gpt'
	@gnuplot 'scripts/g06_plot05.gpt'
	@gnuplot 'scripts/g06_plot06.gpt'
	@cd data; \
	rm avg_rerun.csv avg_iteration.csv avg_deviation.csv freq.csv

debug_prof:
	@cd external/src/; \
	tar zxvf Box2D.tgz -k; \
	cd Box2D; \
	mkdir -p build296; \
	cd build296/; \
	rm -rf *; \
	cmake -DCMAKE_BUILD_TYPE=Debug ../; \
	make $(INSTALL); \
	make
	@make exe_debug
	@cd scripts; \
	chmod +x profile.sh; \
	./profile.sh 2

release_prof:
	@cd external/src/; \
	tar zxvf Box2D.tgz -k; \
	cd Box2D; \
	mkdir -p build296; \
	cd build296/; \
	rm -r *; \
	cmake -DCMAKE_BUILD_TYPE=Release ../; \
	make $(INSTALL); \
	make
	@make exe_release
	@cd scripts; \
	chmod +x profile.sh; \
	./profile.sh 1

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

report:
	@cd doc; \
	latex g06_project_report.tex; \
	bibtex g06_project_report.aux; \
	latex g06_project_report.tex; \
	latex g06_project_report.tex; \
	dvips g06_project_report.dvi; \
	ps2pdf g06_project_report.ps; \
	rm -f *.aux *.dvi *.ps;

$(INSTALL): $(INSTALL)Box2D setup $(BINDIR)/$(TARGET)
	@mkdir -p $(INSTALL)
	@cp -r $(BINDIR) scripts/ doc/ $(INSTALL)/ ;

$(INSTALL)Box2D: 
	@cd external/src; \
	rm -rf Box2D; \
	tar zxvf Box2D.tgz; \
	cd Box2D; \
	mkdir build296; \
	cd build296; \
	cmake ..; \
	make; \
	make $(INSTALL);

dist: clean distclean cleanBox2d
	@cd ..; \
	tar zcvf g06_project.tgz project

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~
	@$(RM) -rf $(OBJDIRANALYSIS) *~ $(DEPS) $(SRCDIR)/*~
	@rm -rf doc/*.aux doc/*.dvi doc/*.ps doc/*.blg doc/*.bbl
	@rm -rf plots $(INSTALL)

distclean: 
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html

cleanBox2d:
	@cd external/src; \
	rm -rf Box2D; \
	cd ../; \
	rm -rf include/*; \
	rm -rf lib/*;
