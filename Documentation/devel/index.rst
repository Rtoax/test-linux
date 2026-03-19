.. SPDX-License-Identifier: GPL-2.0

Development rules
=================

Linus Torvalds releases a new kernel and opens a **2-week merge window**,
however, test-linux has no development cycle restrictions, submissions,
development, and releases can be done at any time.


Commit Tags
===========

- **Signed-off-by**: Using sign-off, developers certify the patch to be their
  original work or have the right to pass it on as an open source patch. In
  our example, the author signed off and then, as the usb maintainer, Greg KH
  signed-off on the patch. Please refer to Sign your work - the Developer's
  Certificate of Origin for detailed information on this tag, as it is a very
  important part of the kernel development process.
- **Acked-by**: This tag is often used by the maintainer of the affected code
  when that maintainer neither contributed to, nor forwarded the patch. As an
  example, I maintain the usbip driver and I use the Acked-by tag to ask the
  USB maintainer to pick patches sent by other developers.
- **Reviewed-by**: This tag indicates that the patch has been reviewed by the
  person named in the tag.
- **Reported-by**: This tag gives credit to people who find bugs and report
  them.
- **Tested-by**: This tag indicates that the patch has been tested by the
  person named in the tag.
- **Suggested-by**: This tag indicates that the patch has been tested by the
  person named in the tag.
- **Fixes**: This tag indicates that the patch fixes an issue in a previous
  commit referenced by its Commit ID. This tag allows us to track where the
  bug originated.
- **Envs**: This tag indicates the env of your system.
- **Vers**: This tag indicates the software/hardware version of your system.
