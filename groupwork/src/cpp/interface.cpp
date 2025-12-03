#include "listnode.hpp"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(linked_list) {
    class_<LinkedList>("LinkedList")
        .constructor<>()
        .function("insertHead", &LinkedList::insertHead)
        .function("insertTail", &LinkedList::insertTail)
        .function("insertAfterId", &LinkedList::insertAfterId)
        .function("deleteById", &LinkedList::deleteById)
        .function("clear", &LinkedList::clear)
        .function("count", &LinkedList::count)
        .function("getMinValue", &LinkedList::getMinValue)
        .function("getMaxValue", &LinkedList::getMaxValue)
        .function("isSingleChain", &LinkedList::isSingleChain)
        .function("reverse", &LinkedList::reverse)
        .function("sortById", &LinkedList::sortById)
        .function("sortByValue", &LinkedList::sortByValue)
        .function("isIdExists", &LinkedList::isIdExists)
        .function("toMermaid", &LinkedList::toMermaid);
}
