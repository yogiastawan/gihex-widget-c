
if(BUILD_EXAMPLES)
    add_executable(gihex_gauge_bar gihex_gauge_bar.c)
    target_link_libraries(gihex_gauge_bar PRIVATE PkgConfig::GTK4 gihex_widget)
    add_test(GihexGaugeBar gihex_gauge_bar)

    add_executable(gihex_circular_step_bar gihex_circular_step_bar.c)
    target_link_libraries(gihex_circular_step_bar PRIVATE PkgConfig::GTK4 gihex_widget)
    add_test(GihexCircularStepBar gihex_circular_step_bar)
endif(BUILD_EXAMPLES)


