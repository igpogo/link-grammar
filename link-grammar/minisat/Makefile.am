
VERSION=2.0.0
MINISAT_VERSION_INFO=2:0:0

libminisat_la_LDFLAGS = -version-info $(MINISAT_VERSION_INFO) -no-undefined

lib_LTLIBRARIES = libminisat.la

libminisat_la_SOURCES = \
	Solver.C Solver.h SolverTypes.h \
	Alg.h BasicHeap.h BoxedVec.h Heap.h Map.h Queue.h Sort.h Vec.h
