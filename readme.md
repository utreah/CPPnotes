Aþaðýdaki sýralama için Resul Muhammed adlý arkadaþa teþekkürler. 
01:
Differences C and C++
02: 
Differences C and C++
03-04:
references, Value categories, Default Argument, Type Deductions
05:
Scope, Namelookup, Inline functions
06:
Type cast, Constexpr, Attributes, Function Overloading
07:
Function Overload Resolution
08:
Classes, Access specifiers, ODR
09:
Classes, This pointer
10:
Constructors, destructors
11:
Copy construstor
12: 
Move constructor, table for constructors
13:
Copy elision, RVO, Conversion constructor, Delegating constructor, Temporary objects
14: 
Friend declaration, Operator overloading(till 17), dynamic objects
18:
Named constructor idiom, static keyword, Singleton pattern, namespace, nested namespace, using declaration
19:
using namespace directive, argument dependent lookup(ADL), unnamed namespace, inline namespace, namespace alias, nested types
20:
Nested types, pimpl(pointer implementation) idiom, 
Composition -> agregation –> association, has-a relationship, is-a relationship, dynamic array, string class, small string optimization.
21:
stringin parametrik yapý kalýplarý, arguments and interpretation introduction, moved from state, string constructors, initializer list, string::npos, capacity
22:
Insert,  resize, erase, pop_back, find(find, rfind, find_first_of, find_last_of, find_first_not_of,  find_last_not_of), starts_with, ends_with, contains, reverse, remove, sort, remove-erase idiom, c_str,  data, swap, shrink_to_fit, replace, substr, getline, stoi, to_string, copy, puts
23:
inheritance(public, private, protected) introduction, access control in inheritance, upcasting, object slicing(basic), multi-level inheritance(basic), direct and indirect inheritance, inheritance and special member functions
24: 
inherited constructor, polymorphic class, abstract and concrete class, virtual and pure virtual function, override, virtual dispatch(+ctor and dtor exceptions), virtual constructor idiom
25: 
vptr(virtual function table pointer), vtable, RTTI(Runtime Type Identification), variant return type, covariance, downcasting errors, virtual destructor, NVI(non-virtual interface idiom), final(final class, final override), private inheritance, private inheritance vs containment, restricted polymorphism, protected inheritance


26:
Multiple inheritance, Diamond formation(DDD – dreadful(deathful) diamond of derivation), virtual inheritance, RTTI(Runtime Type Identification), downcasting, dynamic_cast, typeid, std::type_info, sidecast
27:
Type_id,  exception handling, traditional error handling, terminate(abort, set_terminate, get_terminate)
28:
Std::exception, catch all(…), translating and rethrowing exception, Basic exception guarantee, strong exception guarantee, nofail (nothrow) guarantee, stack unwinding, function try block, exception relation between constructor and destructor, noexcept specifier(nothrow guarantee or nofail guarantee), noexcept operator 
29:
Noexcept, SOLID(“require no more promise no less”), noexcept relation with optimization(move and copy ctor), std::exception_ptr, polymorphic exception idiom, exception dispatcher idiom, nested exception, introduction to generic programming,  template, template parameters (type parameter, non-type parameter, template parameter), template argument, deduction and explicit syntax types, CTAD (Class Template Argument Deduction)
30:
Specialization, Template argument deduction, explicit template argument, default template argument, trailing return type, partial ordering rules
31:
Template instantiation, template functions with auto keyword, auto return type,  class templates
32: 
Class templates, templates in inheritance, auto type deduction in non-type templates, lexicographical compare function, explicit specialization, partial ordering rules, partial specializiation
33:
partial specialization, dependent name, variable template, template constraining, alias template, default arguments in template, perfect forwarding
36: Last class of templates
unary fold expressions, binary fold expressions, Standard C++ Library, STL(Standard Template Library), introduction to containers, iterators, and algorithms(copy, find)
37: 
STL, iterators, iterator types, const_iterator, bool predicate, unary and binary predicate, lambda expressions, closure type, closure object
38:
local class, lambda expressions, IIFE(Immediately Involved Function Expression), mutable, stateless and stateful lambdas, positive lambda idiom, trailing return type, generelized lambda expressions
39: 
IIFE, labmda expressions, initialization assignment split
40:
copy, copy_n, replace, replace_copy_if, remove, remove_if, unique, erase, remove_copy_if, STL containers, vector, data, front
41:
vector functions, capacity, reserve, front, back, at, emplace_bakc, emplace, insert, sort, stable_sort, is_sorted 
42:
partial_sort, partial_sort_copy, partition algorythms, partition, stable_partition, partition_copy, basic structure binding, is_partiotioned, partition_point, heap algorithms, make_heap, pop_heap, sort_heap, deque, iterator invalidation, list
43:
list, linked list, doubly linked list, forward list, associative containers, strict weak ordering, set, multiset, lower bound, upper bound, equal range, insert
44:
set, multiset, emplace, find, count, contains, erase, extract, copy, inserter, transparent function object, emplace_hint, merge, map, multimap, insert, emplace, make_pair
45:
try_emplace, insert_or_assign,  unordered associative containers, hash_set, hash_map,  bucket, bucket_count, load_factor, max_load_factor, std::array
46:
std::array, to_array, container adapters(stack, queue, priority_queue), data structure, ABT (Abstract Data Type), stack, push, top, pop, size, queue, priority_queue, tuple, get, tuple_element, tuple_element_t, tuple_size, tuple_size_v, creating custom structured binding example for tuple
47:
std::tuple with reference, tie, apply, advanced function pointers, pointer to member, member function pointer, functional library, reference_wrapper, generate, ref, cref, std::bind, not_fn
48:
functional library, bind, mem_fn, function, invoke, generate, generate_n, fill_n, sorted_range algorithms, set_intersection, set_union, set_difference, set_symmetric_difference, search
49:
search, search_n, includes, bitset, set, reset, flip, test, any, none, all, to_string, to_ulong, to_ullong, binary search algorithm(binary_search), lower_bound, max, min, max_element, min_element, minmax_element, structure binding
50:
structured binding, dynamic objects, operator new, get_new_handler, set_new_handler, writing our own new_handler, placement new, operator delete
51:
new operator, memory library, pointer-like classes, smart pointers(unique_ptr, shared_ptr and weak_ptr(not so smart) ), unique_ptr (exclusive ownership), default_delete, make_unique, reset, release, get
52:
unique_ptr, partial specialization of unique_ptr for arrays, sink functions, shared_ptr, reference counter, use_count, make_shared