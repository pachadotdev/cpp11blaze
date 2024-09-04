// cpp11eigen version: 0.2.0
// vendored on: 2024-09-02
file(GLOB Eigen_EulerAngles_SRCS "*.h")

install(FILES
  ${Eigen_EulerAngles_SRCS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/unsupported/Eigen/src/EulerAngles COMPONENT Devel
  )
