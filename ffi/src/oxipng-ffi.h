#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum OxiPngResult {
    OxiPngResultOk = 0,
    OxiPngResultDeflatedDataTooLong = 1,
    OxiPngResultTimedOut,
    OxiPngResultNotPng,
    OxiPngResultInvalidData,
    OxiPngResultTruncatedData,
    OxiPngResultAPNGNotSupported,
    OxiPngResultChunkMissing,
    OxiPngResultInvalidPtr,
    OxiPngResultInvalidLen,
    OxiPngResultOther,
};

const char* oxipng_result_description(OxiPngResult res);

typedef struct {
    bool fix_errors;
    bool strip_headers;
    uint8_t level;
} OxiPngOptions;

typedef struct {
    uint8_t* data;
    size_t len;
    size_t capacity;
} OxiPngOutput;


OxiPngResult oxipng_optimize_file(const uint8_t* data, const size_t len, const OxiPngOptions options, OxiPngOutput* output);
void oxipng_output_free(OxiPngOutput* output);

#ifdef __cplusplus
}
#endif
