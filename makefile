CXXFLAGS = -Wall -s -DNDEBUG -O3 -Wno-write-strings
CXXFLAGS1 = -Wall -s -DDEBUG -O3 -Wno-write-strings
CXXFLAGS2 = -Wall -s -DNDEBUG -O3 -Wno-write-strings
CXX=g++

# OBJDIR = ../debug/
OBJDIR = release/
BINDIR = bin/
SRCDIR =src/

makelink = if [ ! -e $(1) ] ; then ln -s $(2)$(1) . ; fi

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	${CXX} ${CXXFLAGS1} -c $< -o$@

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	${CXX} ${CXXFLAGS2} -c $< -o$@

################################################################

tableaurules.o : $(SRCDIR)tableau.cpp $(SRCDIR)refcountedlist.cpp

################################################################

testing2: $(SRCDIR)testing2.cpp $(SRCDIR)refcountedlist.cpp $(SRCDIR)formulaParseTree.cpp \
 ${OBJDIR}formulaOutput.o
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $<  ${OBJDIR}formulaOutput.o ; \
 $(call makelink,$@,${BINDIR})

testing: $(SRCDIR)testing.cpp $(SRCDIR)formulaParseTree.cpp ${OBJDIR}formulaOutput.o
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $<  ${OBJDIR}formulaOutput.o ; \
 $(call makelink,$@,${BINDIR})

proba1: $(SRCDIR)proba1.cpp $(SRCDIR)formulaParseTree.cpp $(SRCDIR)refcountedlist.cpp \
  ${OBJDIR}formulaOutput.o
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $< \
  ${OBJDIR}formulaOutput.o ; $(call makelink,$@,${BINDIR})

proba3: $(SRCDIR)proba3.cpp $(SRCDIR)formulaParseTree.cpp $(SRCDIR)refcountedlist.cpp \
  ${OBJDIR}formulaDestroy.o  ${OBJDIR}formulaOutput.o  ${OBJDIR}flatten.o
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $<  ${OBJDIR}formulaDestroy.o \
  ${OBJDIR}formulaOutput.o  ${OBJDIR}flatten.o ; \
  $(call makelink,$@,${BINDIR})

proba4: $(SRCDIR)proba4.cpp $(SRCDIR)formulaParseTree.cpp $(SRCDIR)refcountedlist.cpp \
  ${OBJDIR}formulaDestroy.o  ${OBJDIR}formulaOutput.o \
  ${OBJDIR}flatten.o  ${OBJDIR}tableaurules.o tableau.cpp
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $<  ${OBJDIR}formulaDestroy.o \
  ${OBJDIR}formulaOutput.o  ${OBJDIR}flatten.o  \
  ${OBJDIR}tableaurules.o ; $(call makelink,$@,${BINDIR})

proba5: $(SRCDIR)proba5.cpp $(SRCDIR)li_tokenizer.cpp  ${OBJDIR}li_tokenizer_private.o
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $<  ${OBJDIR}li_tokenizer_private.o ; \
 $(call makelink,$@,${BINDIR})

proba6: $(SRCDIR)proba6.cpp $(SRCDIR)tokenizer.cpp  ${OBJDIR}tokenizerimpl.o
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $<  ${OBJDIR}tokenizerimpl.o ; \
 $(call makelink,$@,${BINDIR})

proba7: $(SRCDIR)proba7.cpp $(SRCDIR)tokenizer.cpp $(SRCDIR)twostackparser.cpp  ${OBJDIR}formulaOutput.o \
  ${OBJDIR}tokenizerimpl.o  ${OBJDIR}formulaDestroy.o  ${OBJDIR}flatten.o \
  ${OBJDIR}tableaurules.o ${OBJDIR}pstatus.o \
 $(SRCDIR)refcountedlist.cpp $(SRCDIR)tableau.cpp
	${CXX} ${CXXFLAGS} -o ${BINDIR}$@ $< -lreadline -lncurses \
  ${OBJDIR}tokenizerimpl.o ${OBJDIR}pstatus.o\
 ${OBJDIR}formulaOutput.o \
  ${OBJDIR}formulaDestroy.o  ${OBJDIR}flatten.o  ${OBJDIR}tableaurules.o ; \
 $(call makelink,$@,${BINDIR})

alltests: testing testing2 proba1 proba3 proba4 proba5

################################################################

clean: 
	rm -f proba1 proba3 testing testing2

.symlinks:
	ls -F | grep '@' | sed -e "s/\@$$//" > .symlinks ; \
 echo .symlinks >> .symlinks

../processor.tgz: .symlinks
	pushd .. ; tar czf processor.tgz \
 --exclude-from=processor/.symlinks --exclude=processor/*~ processor ; popd

tarball: ../processor.tgz

.PHONY: clean .symlinks tarball alltests
