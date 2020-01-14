**Date**   | <center>**Topics**</center>
:----------|:--------------------------------
Jan  7     | [**Overview and introduction**](slides/lecture1.pdf) <br/> Optional reading: Chapter 0x200 of Hacking
Jan  9     | [**Security foundations**](slides/lecture2.pdf) <br/> Reading: Thompson's [Reflections on Trusting Trust](papers/thompson.pdf), [Ch 1](https://www.cl.cam.ac.uk/~rja14/Papers/SEv2-c01.pdf), and [Ch 4.1-4.2](https://www.cl.cam.ac.uk/~rja14/Papers/SEv2-c04.pdf)
Jan 14     | [**Security foundations (in-class discussion)**](slides/lecture3.pdf) [Kirill's slides](https://cseweb.ucsd.edu/classes/fa17/cse127-b/lec2.pdf)
Jan 16     | [**Stack buffer-overflows**](slides/lecture4.pdf) <br/> Reading: Aleph One's [Smashing the Stack for Fun and Profit](http://phrack.org/issues/49/14.html#article) <br/> Optional reading: 0x300-0x320 from Hacking. 0x200-0x270 if you don't have a strong C background.
Jan 21     | **[MLK](https://en.wikipedia.org/wiki/Martin_Luther_King_Jr.) - no class**
Jan 23     | [**ASLR and W^X**](slides/lecture5.pdf) <br/> Reading: [Eternal War in Memory](papers/eternal-war-in-memory.pdf) by Szekeres et al., [ASLR](https://pax.grsecurity.net/docs/aslr.txt), and [NOEXEC](https://pax.grsecurity.net/docs/noexec.txt)
Jan 28     | [**Return-oriented programming**](slides/lecture6.pdf) <br/> Reading: [On the Effectiveness of Address-Space Randomization](papers/shacham:aslr.pdf) by Shacham et al., [The Geometry of Innocent Flesh on the Bone: Return-into-libc without Function Calls (on the x86)](papers/shacham:rop.pdf) by Shacham, and [Hacking BLind](papers/bittau:brop.pdf) by Bittau et al.
Jan 30     | [**Control flow integrity**](slides/lecture7.pdf) <br/> Reading: [Control-Flow Integrity](papers/abadi:cfi.pdf) by Abadi et al., [Control-Flow Bending: On the Effectiveness of Control-Flow Integrity](papers/carlini:cfb.pdf) by Carlini et al. and [Control-Flow Integrity: Precision, Security, and Performance](papers/burow:cfi.pdf) by Burow et al. 
Feb  4     | **Memory safety** <br/> Reading: [SoftBound: Highly Compatible and CompleteSpatial Memory Safety for C](papers/softbound.pdf) by Nagarakatte et al., [Oscar: A Practical Page-Permissions-Based Scheme for Thwarting Dangling Pointers](papers/dang:oscar.pdf) by Dang et al., and Bringing Memory Safety to WebAssembly by Disselkoen et al.
Feb  6     | [**Least privilege and privilege separation**](slides/lecture9.pdf) <br/> Reading: [Operating Systems Security](papers/ossecurity.pdf) by Jaeger
Feb 11     | [**Isolation** and **short review**](slides/lecture10.pdf) <br/> Reading: [Efficient Software-Based Fault Isolation](papers/wahbe:sfi.pdf) by Wahbe et al.
Feb 12     | **Midterm review**
Feb 13     | **Midterm exam (in-class)**
Feb 18     | **President's day - no class**
Feb 20     | [**Page tables, VMs, and side channels**](slides/lecture11.pdf) <br/> Reading: [Remote Timing Attacks are Practical](papers/brumley:timing.pdf) by Brumley and Boneh
Feb 25     | [**Web security model and CSRF**](https://cseweb.ucsd.edu/classes/fa17/cse127-b/lec11.pdf) <br/> Reading: [CSRF](https://www.owasp.org/index.php/Cross-Site_Request_Forgery_%28CSRF%29) and [Same Origin Policy](https://code.google.com/archive/p/browsersec/wikis/Part2.wiki#Same-origin_policy) <br/> Lecture code: [CSRF simple app](https://github.com/PLSysSec/cse127-toy-webapp)
Feb 27     | [**CSRF, XSS, SQLi**](../notes/lecture13/) <br/> Reading: [XSS Game](https://xss-game.appspot.com/) and [SQL Injection](https://secure.php.net/manual/en/security.database.sql-injection.php)
Mar  4     | [**Modern client-side security mechanisms**](slides/lecture14.pdf) <br/> Reading [CSP](https://www.html5rocks.com/en/tutorials/security/content-security-policy/), [iframe sandbox](https://www.html5rocks.com/en/tutorials/security/sandboxed-iframes/), [CORS](https://developer.mozilla.org/en-US/docs/Web/HTTP/CORS), [SRI](https://developer.mozilla.org/en-US/docs/Web/Security/Subresource_Integrity), [Mixed content](https://developer.mozilla.org/en-US/docs/Web/Security/Mixed_content), [Busting Frame Busting:a Study of Clickjacking Vulnerabilities on Popular Site](papers/rydstedt:busting.pdf) by Rydstedt et al.
Mar  6     | [**Intro to cryptography**](slides/lecture15.pdf) <br/> Reading: [Security Engineering, Ch 5](https://www.cl.cam.ac.uk/~rja14/Papers/SEv2-c05.pdf), [BREACH](http://breachattack.com/resources/BREACH%20-%20SSL,%20gone%20in%2030%20seconds.pdf)
Mar 11     | [**PKI, HTTPS, and CT**](slides/lecture16.pdf) <br/> Reading: [Ten Risks of PKI](papers/ellison:ten-risks.pdf) by Ellison and Schneier, [Towards Short-Lived Certificates](papers/topalovic:towards.pdf) by Topalovic et al., [The New Illustrated TLS Connection](https://tls13.ulfheim.net/), [CT log searches](https://crt.sh), and [CRLite: a Scalable System for Pushing all TLS Revocations to All Browsers](papers/crtlite.pdf) by Larisch et al.
Mar 13     | [**Network security**](https://cseweb.ucsd.edu/classes/fa17/cse127-b/lec15.pdf) <br/> Reading: [A Look Back at Security Problems in the TCP/IP Protocol Suite](papers/bellovin:ip.pdf) by Bellovin, [An Illustrated Guide to the Kaminsky DNS Vulnerability](http://unixwiz.net/techtips/iguide-kaminsky-dns-vuln.html) by Friedl
Mar 20     | **Final exam in Solis 104 @ 7-10PM**