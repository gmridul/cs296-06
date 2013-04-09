.SUFFIXES: .cpp .hpp

# Programs
SHELL = bash
CC = g++
LD	= ld
RM = rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGETexe = cs296_exe_06
TARGETexelib = cs296_exelib_06

# Project Paths
PROJECT_ROOT=$(HOME)/cs296-06
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
MYOBJDIRS = $(PROJECT_ROOT)/myobjs
MYBINDIRS = $(PROJECT_ROOT)/mybins
MYLIBDIRS = $(PROJECT_ROOT)/mylibs
DOCDIR = $(PROJECT_ROOT)/doc

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL
MYLIBS = -lCS296

# Compiler and Linker flags
CPPFLAGS_debug = -g -Wall
CPPFLAGS_release = -g -O3 -Wall
CPPFLAGS = -g -O3 -Wall
CPPFLAGS_debug+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
CPPFLAGS_release+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
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

STATIC_LIB=false
SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
MYOBJS := $(SRCS:$(SRCDIR)/%.cpp=$(MYOBJDIRS)/%.o)
MAINOBJS := $(filter-out $(MYOBJDIRS)/main.o,$(MYOBJS))
BOX2D = "Box2D"

.PHONY: exe exelib doc report clean plot01 plot02 debug_prof release_prof

exe: setup $(MYOBJS)
	@g++ -o $(MYBINDIRS)/$(TARGETexe) $(CPPFLAGS) $(LDFLAGS) $(MYOBJS) $(LIBS) -MD -pg

exe_debug: setup $(MYOBJS)
	@g++ -o $(MYBINDIRS)/$(TARGETexe) $(CPPFLAGS_debug) $(LDFLAGS) $(MYOBJS) $(LIBS) -MD -pg

exe_release: setup $(MYOBJS)
	@g++ -o $(MYBINDIRS)/$(TARGETexe) $(CPPFLAGS_release) $(LDFLAGS) $(MYOBJS) $(LIBS) -MD -pg

setup:
	@mkdir -p myobjs
	@mkdir -p mybins
	@mkdir -p mylibs
	@mkdir -p data plots

$(MYOBJS) : $(MYOBJDIRS)/%.o : $(SRCDIR)/%.cpp
	@g++ $(CPPFLAGS) -fpic -c -Wall $< -o $@ -MD -pg

-include $(MYOBJS:.o=.d)

libraries : $(MYOBJS)
	@if $(STATIC_LIB); \
	then \
		ar rcs $(MYLIBDIRS)/libCS296.a $(MAINOBJS); \
	else \
		g++ -shared -Wl,-soname,libCS296.so -o $(MYLIBDIRS)/libCS296.so $(MAINOBJS) -pg ; \
	fi

exelib : setup libraries
	@g++ -Wl,-rpath, $(CPPFLAGS) $(MYLIBDIRS) -o $(MYBINDIRS)/$(TARGETexelib) $(MYOBJDIRS)/main.o $(LDFLAGS) -L $(MYLIBDIRS) -lCS296 $(LIBS) -pg

debug_prof:
	@cd external/src/; \
	tar zxvf Box2D.tgz -k; \
	cd Box2D; \
	mkdir -p build296; \
	cd build296/; \
	rm -rf *; \
	cmake -DCMAKE_BUILD_TYPE=Debug ../; \
	make install; \
	make
	@make exe_debug
	@chmod +x profile.sh
	@./profile.sh 2

release_prof:
	@cd external/src/; \
	tar zxvf Box2D.tgz -k; \
	cd Box2D; \
	mkdir -p build296; \
	cd build296/; \
	rm -r *; \
	cmake -DCMAKE_BUILD_TYPE=Release ../; \
	make install; \
	make
	@make exe_release
	@chmod +x profile.sh
	@./profile.sh 1

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ... "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

report: setup
	@cd external/src/; \
	if [ ! -d Box2D ]; then \
		tar zxvf Box2D.tgz -k; \
		cd Box2D; \
		mkdir -p build296; \
		cd build296/; \
		rm -r *; \
		cmake -DCMAKE_BUILD_TYPE=Release ../; \
		make install; \
		make; \
	fi
	@make exe_release
	@cd scripts; \
	python3 g06_gen_csv.py; \
	python3 g06_gen_plots.py; \
	cp ../doc/g06_lab09_compare1.png . ;\
	cp ../doc/g06_lab09_compare2.png . ;\
	python3 g06_gen_html.py
# @cd doc; \
# latex report_cs296_06; \
# bibtex report_cs296_06; \
# latex report_cs296_06; \
# latex report_cs296_06; \
# dvipdf report_cs296_06.dvi report_cs296_06.pdf; \
# latex g06_report.tex; \
# dvipdf g06_report.dvi g06_report.pdf; \
# rm *.dvi *.log *.aux *.bbl *.blg

plot02:
	@mkdir -p data plots
	@cd scripts; \
	./gen_data_csv.sh; \
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

clean:
	@rm -rf my*
	@rm -rf $(DOCDIR)/html $(DOCDIR)/*.pdf
	@rm -rf plots
	@rm -rf data
	@rm -rf doc/*.html
	@rm -rf *.dat gmon.out
