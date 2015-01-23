#include "testutils/FuseUtimensTest.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "fspp/fuse/FuseErrnoException.h"

using ::testing::_;
using ::testing::StrEq;
using ::testing::Throw;
using ::testing::WithParamInterface;
using ::testing::Values;

using namespace fspp::fuse;

class FuseUtimensErrorTest: public FuseUtimensTest, public WithParamInterface<int> {
};
INSTANTIATE_TEST_CASE_P(FuseUtimensErrorTest, FuseUtimensErrorTest, Values(EACCES, ENOENT, EPERM, EROFS));

TEST_P(FuseUtimensErrorTest, ReturnedErrorIsCorrect) {
  ReturnIsFileOnLstat(FILENAME);
  EXPECT_CALL(fsimpl, utimens(StrEq(FILENAME), _))
    .Times(1).WillOnce(Throw(FuseErrnoException(GetParam())));

  int error = UtimensReturnError(FILENAME, TIMEVALUES);
  EXPECT_EQ(GetParam(), error);
}