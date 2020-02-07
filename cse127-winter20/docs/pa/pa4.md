# Assignment 4 *80pts*

**Deadline: Wednesday, February 19, 2029 by 13:59:59**

**Early Turn-In: Sunday, February 16, 2019 by 23:59:59(10% bonus)**

## Overview

The goal of this assignment is to gain hands-on experience exploiting vulnerabilities on websites. This assignment will demonstrate how simple vulnerabilities (often occurring due to the carelessness of the website developer) can be really harmful to the website's owners. Security attacks include but aren't limited to stealing sensitive information, injecting malicious code, and causing the host server to crash.

In this assignment, you have 8 'levels' or 'challenges' (each worth 10 points). In each challenge, you have to find the 'flag'. A flag is just a secret password that you need to find by exploiting certain vulnerabilities. Once you have the password, just enter it in the text box and hit the submit button to move up one level. Every challenge comes with hints and clues (present as text on the web page itself) which will guide you through exploiting a particular vulnerability. You may consult any online references you wish.

## Getting Started/Logging In

Visit [https://c10-32.sysnet.ucsd.edu/challenges/](https://c10-32.sysnet.ucsd.edu/challenges/). In this page, you will be asked to enter your PID and a password. You can find your password in your Gradescope account for this class (look for the "Assignment 4 userinfo" assignment).

## A Word of Caution

Each level comes with a description of its password. As mentioned before, every password is completely randomized for every level, and the fastest way to get to the password is by exploiting the said vulnerability. It should also be noted that brute-force techniques will not work. We have kept limits on the number of ping and http connections that every account can send to our server each day. If you reach this limit, you will be blocked for the rest of the day. So please do not try to DDOS the server with random tries.

## Prior Knowledge

During the assignment, you may encounter situations that may require to either execute HTML, Client-side JavaScript or SQL statements. Some levels can be solved with a few lines written in Python. However, no code that you are expected to write in this assignment exceeds 10 (very small) lines. Most of the expected code is pretty generic and can be found with a quick Google search. The aim of the assignment is not to teach you coding in the said languages, but to give you hands-on experience with the tricks that most "hackers" or exploiters use in today's world. During no time are you expected to know "truly fancy" stuff like PHP, ASP, server-side JavaScript, AJAX, JQuery, Flash, CSS or in general - anything beyond the realms of the aforementioned techniques.

## Useful Resources

Here are few resources which you may find very helpful while solving the assignment. They are, in no particular order:

1. GET and POST requests - <a href="https://www.w3schools.com/tags/ref_httpmethods.asp">https://www.w3schools.com/tags/ref_httpmethods.asp</a>
2. Python Requests library - <a href="http://docs.python-requests.org/en/master/">http://docs.python-requests.org/en/master/</a>
3. Handling Cookies on your browser - <a href="https://kb.iu.edu/d/ajfi">https://kb.iu.edu/d/ajfi</a>
4. Intro to JavaScript - <a href="https://www.w3schools.com/js/default.asp">https://www.w3schools.com/js/default.asp</a>
5. Intro to SQL - <a href="https://www.w3schools.com/sql/sql_intro.asp">https://www.w3schools.com/sql/sql_intro.asp</a>
6. Base64 Library (Python) Encoding and Decoding - <a href="https://code.tutsplus.com/tutorials/base64-encoding-and-decoding-using-python--cms-25588" >https://code.tutsplus.com/tutorials/base64-encoding-and-decoding-using-python--cms-25588</a>

## Final Notes

Exploiting vulnerabilities on web services is perhaps as old as the web. This assignment is designed to give you a first-hand feel of what people who exploit vulnerabilities look at. It is intended to make you think about these vulnerabilities, whenever you design a web service of your own.

However, since it is intended for academic purposes, it is heavily toned down. Think of it as a toy model of the real world. We have even included hints and descriptions on every level. Just following these and only these should be enough to get you through. In the real world, the "hacker" will not have any hints and will have to systematically try everything. This is often long and meticulous, and not suited for assignment format. Hence, your best friends are the hints present in every level.

Happy hacking!
