#ifndef StHbtResultsWriterCollection_hh
#define StHbtResultsWriterCollection_hh
#include <list>

#include "StHbtMaker/Infrastructure/StHbtResultsWriter.hh"

#if !defined(ST_NO_NAMESPACES)
using std::list;
#endif

#ifdef ST_NO_TEMPLATE_DEF_ARGS
typedef list<StHbtResultsWriter*, allocator<StHbtResultsWriter*> > StHbtResultsWriterCollection;
typedef list<StHbtResultsWriter*, allocator<StHbtResultsWriter*> >::iterator StHbtResultsWriterIterator;
#else
typedef list<StHbtResultsWriter*> StHbtResultsWriterCollection;
typedef list<StHbtResultsWriter*>::iterator StHbtResultsWriterIterator;
#endif

#endif
