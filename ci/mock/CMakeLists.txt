find_package (Python3 COMPONENTS Interpreter)

set(TEXTURES_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Data/Textures)

set(ALL_MESHES_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Data)
set(ALL_MESHES_OUTPUT ${ALL_MESHES_BINARY_DIR}/AllMeshes.g3d)

set(SKY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Data/WeatherSystem)
set(SKY_OUTPUT ${SKY_BINARY_DIR}/sky.l3d)
set(SKY_MESH_FILE ${SKY_BINARY_DIR}/sky.gltf)

set(TERRAIN_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Data/Landscape)
set(TERRAIN_TYPE 0)
set(TERRAIN_OUTPUT ${TERRAIN_BINARY_DIR}/Land1.lnd)
set(TERRAIN_NOISE_MAP ${TERRAIN_BINARY_DIR}/noise_map.r8.raw)
set(TERRAIN_BUMP_MAP ${TERRAIN_BINARY_DIR}/bump_map.r8.raw)
list(APPEND TERRAIN_MATERIAL_ARRAY ${TERRAIN_BINARY_DIR}/material_data1.rgb5a1.raw)
list(APPEND TERRAIN_MATERIAL_ARRAY ${TERRAIN_BINARY_DIR}/material_data2.rgb5a1.raw)
list(APPEND TERRAIN_MATERIAL_ARRAY ${TERRAIN_BINARY_DIR}/material_data3.rgb5a1.raw)
string(REPLACE ";" "," TERRAIN_MATERIAL_LIST "${TERRAIN_MATERIAL_ARRAY}")

# TODO: Combine all texture generating scripts into a single one

add_custom_target(generate-mock-game-data
  COMMAND ${CMAKE_COMMAND} -E make_directory ${TEXTURES_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ALL_MESHES_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SKY_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${TERRAIN_BINARY_DIR}
  # Copy the Scripts Directory
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Scripts ${CMAKE_CURRENT_BINARY_DIR}/Scripts
  # Generate Mock Textures
  COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/Data/Textures/gen_textures.py --output-dir ${TEXTURES_BINARY_DIR}
  # Data/AllMeshes.g3d
  COMMAND g3dtool -w ${ALL_MESHES_OUTPUT}
  # Data/Landscape/Land1.lnd
  COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/Data/Landscape/gen_land_textures.py --output-dir ${TERRAIN_BINARY_DIR}
  COMMAND lndtool write -o ${TERRAIN_OUTPUT} --terrain-type ${TERRAIN_TYPE} --noise-map ${TERRAIN_NOISE_MAP} --bump-map ${TERRAIN_BUMP_MAP} --material-array=${TERRAIN_MATERIAL_LIST}
  # Data/WeatherSystem/sky.l3d
  COMMAND Python3::Interpreter ${CMAKE_CURRENT_SOURCE_DIR}/Data/WeatherSystem/gen_sky.py --output-dir ${SKY_BINARY_DIR}
  COMMAND l3dtool write -o ${SKY_OUTPUT} -i ${SKY_MESH_FILE}

  COMMENT "Generating mock game data in ${CMAKE_CURRENT_BINARY_DIR}"

  BYPRODUCTS
    ${SKY_MESH_FILE}
    ${TERRAIN_NOISE_MAP}
    ${TERRAIN_BUMP_MAP}
    ${TERRAIN_MATERIAL_ARRAY}

  SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Data/Textures/gen_textures.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Data/Landscape/gen_land_textures.py
    ${CMAKE_CURRENT_SOURCE_DIR}/Data/WeatherSystem/gen_sky.py
)
