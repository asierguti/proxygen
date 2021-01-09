/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <proxygen/lib/http/codec/DefaultHTTPCodecFactory.h>

#include <folly/portability/GTest.h>
#include <proxygen/lib/http/codec/HTTP1xCodec.h>
#include <proxygen/lib/http/codec/HTTP2Codec.h>
#include <proxygen/lib/http/codec/HTTP2Constants.h>
#include <proxygen/lib/http/codec/SPDYCodec.h>

using namespace proxygen;

TEST(DefaultHTTPCodecFactoryTest, GetCodec) {
  DefaultHTTPCodecFactory factory(false);

  auto codec = factory.getCodec("spdy/3.1", TransportDirection::UPSTREAM, true);
  SPDYCodec* spdyCodec = dynamic_cast<SPDYCodec*>(codec.get());
  EXPECT_NE(spdyCodec, nullptr);

  codec = factory.getCodec(
      http2::kProtocolString, TransportDirection::UPSTREAM, true);
  HTTP2Codec* http2Codec = dynamic_cast<HTTP2Codec*>(codec.get());
  EXPECT_NE(http2Codec, nullptr);

  codec = factory.getCodec("http/1.1", TransportDirection::UPSTREAM, true);
  HTTP1xCodec* http1xCodec = dynamic_cast<HTTP1xCodec*>(codec.get());
  EXPECT_NE(http1xCodec, nullptr);

  codec = factory.getCodec("", TransportDirection::UPSTREAM, true);
  http1xCodec = dynamic_cast<HTTP1xCodec*>(codec.get());
  EXPECT_NE(http1xCodec, nullptr);

  codec = factory.getCodec("not/supported", TransportDirection::UPSTREAM, true);
  http1xCodec = dynamic_cast<HTTP1xCodec*>(codec.get());
  EXPECT_NE(http1xCodec, nullptr);
}
