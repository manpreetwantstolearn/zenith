# =============================================================================
# Container Build Targets
# =============================================================================
# Provides targets for building and pushing container images to ghcr.io
#
# Targets:
#   image-release  - Build release container image
#   image-debug    - Build debug container image
#   push-release   - Push release image to registry
#   push-debug     - Push debug image to registry
#   prepare-libs   - Copy runtime libraries for container
#   clean-libs     - Remove copied runtime libraries
# =============================================================================

set(CONTAINER_IMAGE_NAME "uri-shortener")
set(CONTAINER_REGISTRY "ghcr.io/manpreetwantstolearn")
set(CONTAINER_DOCKERFILE "${CMAKE_SOURCE_DIR}/apps/uri_shortener/Dockerfile")
set(CONTAINER_LIBS_DIR "${CMAKE_SOURCE_DIR}/libs-runtime")

# Library patterns to copy (matching Makefile behavior)
set(LIB_PATTERNS
    "mongoc"
    "bson"
    "mongocxx"
    "bsoncxx"
    "opentelemetry"
    "nghttp2_asio"
    "redis"
)

# Generate the copy commands for libraries
set(LIB_COPY_COMMANDS "")
foreach(pattern ${LIB_PATTERNS})
    list(APPEND LIB_COPY_COMMANDS
        COMMAND sh -c "cp -f /usr/local/lib/lib${pattern}*.so* ${CONTAINER_LIBS_DIR}/ 2>/dev/null || true"
    )
endforeach()

# Prepare runtime libraries
add_custom_target(prepare-libs
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CONTAINER_LIBS_DIR}
    ${LIB_COPY_COMMANDS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Copying runtime libraries to libs-runtime/"
)

# Build release container image
add_custom_target(image-release
    DEPENDS prepare-libs
    COMMAND buildah bud -f ${CONTAINER_DOCKERFILE} --target release -t ${CONTAINER_IMAGE_NAME}:v1 .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building release container: ${CONTAINER_IMAGE_NAME}:v1"
)

# Build debug container image
add_custom_target(image-debug
    DEPENDS prepare-libs
    COMMAND buildah bud -f ${CONTAINER_DOCKERFILE} --target debug -t ${CONTAINER_IMAGE_NAME}:v1-debug .
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Building debug container: ${CONTAINER_IMAGE_NAME}:v1-debug"
)

# Push release image to registry
add_custom_target(push-release
    COMMAND buildah tag ${CONTAINER_IMAGE_NAME}:v1 ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:v1
    COMMAND buildah tag ${CONTAINER_IMAGE_NAME}:v1 ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:latest
    COMMAND buildah push ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:v1
    COMMAND buildah push ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:latest
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Pushing ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:v1"
)

# Push debug image to registry
add_custom_target(push-debug
    COMMAND buildah tag ${CONTAINER_IMAGE_NAME}:v1-debug ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:v1-debug
    COMMAND buildah push ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:v1-debug
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Pushing ${CONTAINER_REGISTRY}/${CONTAINER_IMAGE_NAME}:v1-debug"
)

# Clean runtime libraries
add_custom_target(clean-libs
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CONTAINER_LIBS_DIR}
    COMMENT "Removing libs-runtime/"
)
