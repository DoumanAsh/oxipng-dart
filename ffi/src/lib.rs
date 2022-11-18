#![cfg_attr(feature = "cargo-clippy", allow(clippy::style))]

use core::{mem, ptr, slice};

#[repr(C)]
pub enum OxiPngResult {
    Ok = 0,
    DeflatedDataTooLong = 1,
    TimedOut,
    NotPng,
    InvalidData,
    TruncatedData,
    APNGNotSupported,
    ChunkMissing,
    InvalidPtr,
    InvalidLen,
    Other,
}

impl Into<OxiPngResult> for oxipng::PngError {
    #[inline]
    fn into(self) -> OxiPngResult {
        match self {
            oxipng::PngError::DeflatedDataTooLong(_) => OxiPngResult::DeflatedDataTooLong,
            oxipng::PngError::TimedOut => OxiPngResult::TimedOut,
            oxipng::PngError::NotPNG => OxiPngResult::NotPng,
            oxipng::PngError::InvalidData => OxiPngResult::InvalidData,
            oxipng::PngError::TruncatedData => OxiPngResult::TruncatedData,
            oxipng::PngError::APNGNotSupported => OxiPngResult::APNGNotSupported,
            oxipng::PngError::ChunkMissing(_) => OxiPngResult::ChunkMissing,
            _ => OxiPngResult::Other,
        }
    }
}

#[no_mangle]
pub unsafe extern "C" fn oxipng_result_description(code: OxiPngResult) -> *const i8 {
    let res = match code {
        OxiPngResult::Ok => "No error\0".as_ptr(),
        OxiPngResult::DeflatedDataTooLong => "Deflated data too long\0".as_ptr(),
        OxiPngResult::TimedOut => "Timeout\0".as_ptr(),
        OxiPngResult::NotPng  => "Invalid header detected; Not a PNG file\0".as_ptr(),
        OxiPngResult::InvalidData => "Invalid data found; unable to read PNG file\0".as_ptr(),
        OxiPngResult::TruncatedData => "Missing data in the file; the file is incomplete\0".as_ptr(),
        OxiPngResult::APNGNotSupported => "APNG files are not (yet) supported\0".as_ptr(),
        OxiPngResult::ChunkMissing => "missing chunk\0".as_ptr(),
        OxiPngResult::InvalidPtr => "Internal ptr error\0".as_ptr(),
        OxiPngResult::InvalidLen => "Internal len error\0".as_ptr(),
        OxiPngResult::Other => "Unexpected error\0".as_ptr(),
    };
    res as _
}

#[repr(C)]
pub struct OxiPngOptions {
    fix_errors: bool,
    strip_headers: bool,
    level: u8,
}

impl Into<oxipng::Options> for OxiPngOptions {
    fn into(self) -> oxipng::Options {
        let mut result = oxipng::Options::from_preset(self.level);
        result.fix_errors = self.fix_errors;
        if self.strip_headers {
            result.strip = oxipng::Headers::Safe;
        }
        result
    }
}

#[repr(C)]
pub struct OxiPngOutput {
    data: *mut u8,
    len: usize,
    capacity: usize,
}

#[no_mangle]
pub unsafe extern "C" fn oxipng_output_free(output: *mut OxiPngOutput) {
    if let Some(output) = output.as_mut() {
        if !output.data.is_null() {
            Vec::from_raw_parts(output.data, output.len, output.capacity);
            output.data = ptr::null_mut();
        }
    }
}

#[no_mangle]
pub unsafe extern "C" fn oxipng_optimize_file(data: *const u8, len: usize, options: OxiPngOptions, output: *mut OxiPngOutput) -> OxiPngResult {
    if data.is_null() || output.is_null() {
        return OxiPngResult::InvalidPtr;
    } else if len <= 8 {
        return OxiPngResult::InvalidLen;
    };

    let data = slice::from_raw_parts(data, len);

    match oxipng::optimize_from_memory(data, &options.into()) {
        Ok(result) => {
            let mut result = mem::ManuallyDrop::new(result);
            let output = &mut *output;
            output.data = result.as_mut_ptr();
            output.len = result.len();
            output.capacity = result.capacity();
            OxiPngResult::Ok
        },
        Err(error) => error.into()
    }
}
