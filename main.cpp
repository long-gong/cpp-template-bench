#include <iostream>

#include <benchmark/benchmark.h>

namespace temp_impl {

namespace detail {
static float _diff[128];
// Type your code here, or load an example.
template<int b>
struct LoopUnrollingBlock {
  static inline float apply(const float *va, const float *vb, float *diff) {
    diff[0] = va[0] - vb[0];
    return diff[0] * diff[0] + LoopUnrollingBlock<b - 1>::apply(va + 1, vb + 1, diff + 1);
  }
};

template<>
struct LoopUnrollingBlock<1> {
  static inline float apply(const float *va, const float *vb, float *diff) {
    diff[0] = va[0] - vb[0];
    return diff[0] * diff[0];
  }
};
}// end namespace detail

float l2_sqr(const float *a, const float *b, int dim) {
  constexpr int block = 32;
  float dist = 0;
  for (int i = 0; i < dim; i += block) {
    dist += detail::LoopUnrollingBlock<block>::apply(a + i, b + i, detail::_diff);
  }
  return dist;
}

}

namespace no_temp_impl {

namespace detail {
static float _diff[32];

inline float l2_sqr_block32(const float *va, const float *vb) {
  _diff[0] = va[0] - vb[0];
  _diff[1] = va[1] - vb[1];
  _diff[2] = va[2] - vb[2];
  _diff[3] = va[3] - vb[3];
  _diff[4] = va[4] - vb[4];
  _diff[5] = va[5] - vb[5];
  _diff[6] = va[6] - vb[6];
  _diff[7] = va[7] - vb[7];
  _diff[8] = va[8] - vb[8];
  _diff[9] = va[9] - vb[9];
  _diff[10] = va[10] - vb[10];
  _diff[11] = va[11] - vb[11];
  _diff[12] = va[12] - vb[12];
  _diff[13] = va[13] - vb[13];
  _diff[14] = va[14] - vb[14];
  _diff[15] = va[15] - vb[15];
  _diff[16] = va[16] - vb[16];
  _diff[17] = va[17] - vb[17];
  _diff[18] = va[18] - vb[18];
  _diff[19] = va[19] - vb[19];
  _diff[20] = va[20] - vb[20];
  _diff[21] = va[21] - vb[21];
  _diff[22] = va[22] - vb[22];
  _diff[23] = va[23] - vb[23];
  _diff[24] = va[24] - vb[24];
  _diff[25] = va[25] - vb[25];
  _diff[26] = va[26] - vb[26];
  _diff[27] = va[27] - vb[27];
  _diff[28] = va[28] - vb[28];
  _diff[29] = va[29] - vb[29];
  _diff[30] = va[30] - vb[30];
  _diff[31] = va[31] - vb[31];
  return _diff[0] * _diff[0] + _diff[1] * _diff[1] + _diff[2] * _diff[2] + _diff[3] * _diff[3] + _diff[4] * _diff[4]
      + _diff[5] * _diff[5] + _diff[6] * _diff[6] + _diff[7] * _diff[7] + _diff[8] * _diff[8] + _diff[9] * _diff[9]
      + _diff[10] * _diff[10] + _diff[11] * _diff[11] + _diff[12] * _diff[12] + _diff[13] * _diff[13]
      + _diff[14] * _diff[14] + _diff[15] * _diff[15] + _diff[16] * _diff[16] + _diff[17] * _diff[17]
      + _diff[18] * _diff[18] + _diff[19] * _diff[19] + _diff[20] * _diff[20] + _diff[21] * _diff[21]
      + _diff[22] * _diff[22] + _diff[23] * _diff[23] + _diff[24] * _diff[24] + _diff[25] * _diff[25]
      + _diff[26] * _diff[26] + _diff[27] * _diff[27] + _diff[28] * _diff[28] + _diff[29] * _diff[29]
      + _diff[30] * _diff[30] + _diff[31] * _diff[31];
}
}
    float l2_sqr(const float *va, const float *vb, int dim) {
        float dist = 0;
        for(int i = 0;i < dim;i += 32) {
            dist += detail::l2_sqr_block32(va + i, vb + i);
        }
        return dist;
    }
}

static void BM_Temp(benchmark::State& state) {
  float va[256];
  float vb[256];
  for (int i = 0;i < 256;++ i) {
    va[i] = i + 1;
    vb[i] = 256 - i + 1;
  }
  for (auto _ : state)
    temp_impl::l2_sqr(va, vb, 256);
}
// Register the function as a benchmark
BENCHMARK(BM_Temp);

// Define another benchmark
static void BM_NonTemp(benchmark::State& state) {
  float va[256];
  float vb[256];
  for (int i = 0;i < 256;++ i) {
    va[i] = i + 1;
    vb[i] = 256 - i + 1;
  }
  for (auto _ : state)
    no_temp_impl::l2_sqr(va, vb, 256);
}
BENCHMARK(BM_NonTemp);

BENCHMARK_MAIN();