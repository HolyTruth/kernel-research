"""Contains tests for the Target class."""

import unittest
from target import Target


MOCK_DB_DIR = "test/mock_db"
RELEASES_DIR = f"{MOCK_DB_DIR}/releases"


class TargetTests(unittest.TestCase):
  """Tests for the Target class."""

  def setUp(self):
    super().setUp()
    self.target = Target("kernelctf", "lts-6.1.36",
                         f"{RELEASES_DIR}/kernelctf/lts-6.1.36")

  def test_get_version(self):
    self.assertEqual("KernelCTF version 6.1.36 (...)",
                     self.target.get_version())

  def test_get_symbols(self):
    self.assertDictEqual({
        "prepare_kernel_cred": 0x1befb0,
        "init_nsproxy": 0x26765c0,
        "anon_pipe_buf_ops": 0x1a1cf80,
        "msleep": 0x2292e0,
    }, self.target.get_symbols())
