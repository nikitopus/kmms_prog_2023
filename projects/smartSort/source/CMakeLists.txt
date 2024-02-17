target_sources(smartSort 
	PRIVATE
		io_array.cpp
		io_array.hpp
		menu.cpp
		menu.hpp
		npushkarev_sort.cpp
		bubble_sort.hpp
)

target_include_directories(smartSort PRIVATE
	"${PROJECT_SOURCE_DIR}/source"
)
