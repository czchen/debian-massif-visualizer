include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(visualizer_SRCS
    totalcostmodel.cpp
    detailedcostmodel.cpp
    datatreemodel.cpp
    filtereddatatreemodel.cpp
    dotgraphgenerator.cpp
    util.cpp
)

kde4_add_library(mv-visualizer ${visualizer_SRCS})

target_link_libraries(mv-visualizer
    mv-massifdata
    mv-kdchart
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${KDE4_KDECORE_LIBS}
)
install(TARGETS mv-visualizer ${INSTALL_TARGETS_DEFAULT_ARGS})