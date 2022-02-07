#!usr/bin
sentry-cli difutil check bazel-bin/minidumper/minidumper

objcopy --only-keep-debug bazel-bin/minidumper/minidumper bazel-bin/minidumper/minidumper.debug
objcopy  --strip-debug --strip-unneeded bazel-bin/minidumper/minidumper
objcopy --add-gnu-debuglink=bazel-bin/minidumper/minidumper.debug bazel-bin/minidumper/minidumper

sentry-cli difutil check bazel-bin/minidumper/minidumper.debug
sentry-cli difutil check bazel-bin/minidumper/minidumper

sentry-cli --auth-token $SENTRY_AUTH_TOKEN  upload-dif --log-level=info --org $SENTRY_ORG --project $SENTRY_PROJECT --include-sources ./
