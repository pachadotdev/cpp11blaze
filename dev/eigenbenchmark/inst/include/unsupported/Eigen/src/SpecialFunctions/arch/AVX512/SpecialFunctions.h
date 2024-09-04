// cpp11eigen version: 0.2.0
// vendored on: 2024-09-02
#ifndef EIGEN_AVX512_SPECIALFUNCTIONS_H
#define EIGEN_AVX512_SPECIALFUNCTIONS_H

namespace Eigen {
namespace internal {

F16_PACKET_FUNCTION(Packet16f, Packet16h, perf)
BF16_PACKET_FUNCTION(Packet16f, Packet16bf, perf)

F16_PACKET_FUNCTION(Packet16f, Packet16h, pndtri)
BF16_PACKET_FUNCTION(Packet16f, Packet16bf, pndtri)

}  // namespace internal
}  // namespace Eigen

#endif  // EIGEN_AVX512_SPECIAL_FUNCTIONS_H
