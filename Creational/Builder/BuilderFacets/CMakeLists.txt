add_library(Person Person.cpp)
add_library(PersonBuilder PersonBuilder.cpp)

add_executable(BuilderFacets Facets.cpp)
target_link_libraries(BuilderFacets Person PersonBuilder)