set (src gihex_gauge_bar.c
        gihex_color.c)

if(BUILD_SHARED)
add_library(gihex_widget SHARED ${src})
else()
add_library(gihex_widget STATIC ${src})
endif(BUILD_SHARED)

target_link_libraries(gihex_widget  PRIVATE PkgConfig::GTK4)