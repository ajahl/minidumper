# Copyright 2022 The Magma Authors.

# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

load("@rules_cc//cc:defs.bzl", "cc_library")

LIB_LINUX = [
    "src/client/minidump_file_writer.cc",
    "src/common/convert_UTF.h",
    "src/common/convert_UTF.cc",
    "src/common/md5.cc",
    "src/common/simple_string_dictionary.cc",
    "src/common/string_conversion.cc",
    "src/client/linux/crash_generation/crash_generation_client.cc",
    "src/client/linux/dump_writer_common/thread_info.cc",
    "src/client/linux/dump_writer_common/ucontext_reader.cc",
    "src/client/linux/handler/exception_handler.cc",
    "src/client/linux/handler/minidump_descriptor.cc",
    "src/client/linux/log/log.cc",
    "src/client/linux/microdump_writer/microdump_writer.cc",
    "src/client/linux/minidump_writer/linux_dumper.cc",
    "src/client/linux/minidump_writer/linux_ptrace_dumper.cc",
    "src/client/linux/minidump_writer/minidump_writer.cc",
    "src/common/linux/elfutils.cc",
    "src/common/linux/file_id.cc",
    "src/common/linux/guid_creator.cc",
    "src/common/linux/linux_libc_support.cc",
    "src/common/linux/memory_mapped_file.cc",
    "src/common/linux/safe_readlink.cc",
]

cc_library(
    name = "breakpad",
    srcs =  LIB_LINUX,
    hdrs = glob(["src/**/*.h"]),
    copts = [
            "-Wno-deprecated",
            "-D__STDC_FORMAT_MACROS"
        ],
    linkopts = ["-lpthread"],
    strip_include_prefix = "src",
    visibility = ["//visibility:public"],
    deps = ["@lss"],
)
