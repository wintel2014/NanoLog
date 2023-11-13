/* Copyright (c) 2018 Stanford University
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

 /**
  * This file demonstrates the usage of the NanoLog API through the
  * implementation of simple benchmarking application that reports the
  * average latency and throughput of the NanoLog system.
  */
#include <chrono>

// Required to use the NanoLog system
#include "NanoLogCpp17.h"

void runBenchmark();

// Optional: Import the NanoLog log levels into the current namespace; this
// allows the log levels (DEBUG, INFO, WARN, ERROR) to be used without
// using the NanoLog namespace (i.e. NanoLog::DEBUG).
using namespace NanoLog::LogLevels;

int main(int argc, char** argv) {
    // Optional: Set the output location for the NanoLog system. By default
    // the log will be output to ./compressedLog
    NanoLog::setLogFile("xxx");

    // Optional optimization: pre-allocates thread-local data structures
    // needed by NanoLog. This can be invoked once per new
    // thread that will use the NanoLog system.
    NanoLog::preallocate();

    // Optional: Set the minimum LogLevel that log messages must have to be
    // persisted. Valid from least to greatest values are
    // DEBUG, INFO, WARN, ERROR
    NanoLog::setLogLevel(INFO);

    // NANO_LOG(DEBUG, "Another message.");

    // All the standard printf specifiers (except %n) can be used
    char randomString[] = "Hello World";
    uint64_t aa = 1697420100050000000;
    uint32_t bb = 123;
    NANO_LOG(INFO, "A string, pointer, number, "
                   "and float: %s, %s, %d, %f %lu %u",
             randomString ? "true" : " false",
             randomString,
             512,
             3.14159,
             aa,
             bb);

    // Even with width and length specifiers
    // NANO_LOG(INFO, "Shortend String: %5s and shortend float %0.2lf",
    //                  randomString,
    //                  3.14159);


    // runBenchmark();

    // Optional: Flush all pending log messages to disk
    NanoLog::sync();

    // Optional: Gather statics generated by NanoLog
    // std::string stats = NanoLog::getStats();
    // printf("%s", stats.c_str());

    // Optional: Prints NanoLog configuration parameters
    // NanoLog::printConfig();
}

void runBenchmark() {
    const uint64_t RECORDS = 1000;

    std::chrono::high_resolution_clock::time_point start, stop;
    double time_span;

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < RECORDS; ++i) {
        // NANO_LOG(INFO, "Simple log message with 0 parameters");
    }
    stop = std::chrono::high_resolution_clock::now();

    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
                                                        stop - start).count();
    printf("The total time spent invoking NANO_LOG with no parameters %lu "
            "times took %0.2lf seconds (%0.2lf ns/message average)\r\n",
            RECORDS, time_span, (time_span/RECORDS)*1e9);

    start = std::chrono::high_resolution_clock::now();
    // Flush all pending log messages to disk
    NanoLog::sync();
    stop = std::chrono::high_resolution_clock::now();

    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(
                                                        stop - start).count();
    printf("Flushing the log statements to disk took an additional "
                "%0.2lf secs\r\n", time_span);
}

