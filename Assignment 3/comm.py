#!/usr/bin/python                                                                                                                                                                  

import random, sys, locale
from optparse import OptionParser

def main():
    locale.setlocale(locale.LC_ALL, 'C')
    version_msg = "%prog 2.0"                                                                                                                                                      
    usage_msg = """%prog [OPTION]... FILE1 FILE2
        
        Output the comparison results between FILE1 and FILE2 in three columns."""
    
    parser = OptionParser(version=version_msg, usage=usage_msg)  
    parser.add_option("-1", action="store_true", dest="suppress1",
                      default = False,
                      help="suppress column 1 (lines unique to FILE1)")
    parser.add_option("-2", action="store_true", dest="suppress2",
                      default = False,
                      help="suppress column 2 (lines unique to FILE2)")
    parser.add_option("-3", action="store_true", dest="suppress3",
                      default = False,
                      help="suppress column 3 (lines that appear in both files)")
    parser.add_option("-u", action="store_true", dest="unsort",
                      default = False,
                      help="run comparison on unsorted files line by line." )
    options, args = parser.parse_args(sys.argv[1:])
    if len(args)!=2:
        parser.error("Missing option arguments")
    file1=args[0]
    file2=args[1]
    lines1 = []
    lines2 = []
    if file2=="-":
        lines1=sys.stdin.readlines()
        try:
            f2 = open (file1, 'r')
            lines2 = f2.readlines()
            f2.close()
        except:
            parser.error("Invalid file")
    elif file1=="-":
        lines2=sys.stdin.readlines()
        try:
            f1 = open (file2, 'r')
            lines1 = f1.readlines()
            f1.close()
        except:
            parser.error("Invalid file")
    elif file1=="-" and file2=="-":
        exit()
    else:
        try:
            f1 = open (file1, 'r')
            f2 = open (file2, 'r')
            lines1 = f1.readlines()
            lines2 = f2.readlines()
            f1.close()
            f2.close()
        except:
            parser.error("Invalid file")
    unsort=options.unsort
    suppress1=options.suppress1
    suppress2=options.suppress2
    suppress3=options.suppress3
    sp="        "
    n1 = len(lines1)
    n2 = len(lines2)
    col1 = []
    col2 = []
    col3 = []
    n=0
    if unsort==0:
        col3=[i for i in lines1 if i in lines2]
        for i in col3:
            if i in lines2:
                lines2.remove(i)
        for i in col3:
            if i in lines1:
                lines1.remove(i)
        t=sorted(lines1+col3+lines2)
        col1=lines1
        col2=lines2
        for i in t:
            if i in col1 and suppress1!=1:
                sys.stdout.write(i)
            if i in col2 and suppress1!=1 and suppress2!=1:
                sys.stdout.write(sp+i)
            elif i in col2 and suppress1==1 and suppress2!=1:
                sys.stdout.write(i)

            if i in col3 and suppress1!=1 and suppress2!=1 and suppress3!=1:
                sys.stdout.write(sp+sp+i)
            elif i in col3 and suppress1==1 and suppress2!=1 and suppress3!=1:
                sys.stdout.write(sp+i)
            elif i in col3 and suppress1!=1 and suppress2==1 and suppress3!=1:
                sys.stdout.write(sp+i)
            elif i in col3 and suppress1==1 and suppress2==1 and suppress3!=1:
                sys.stdout.write(i)
    if unsort==1:
        col3=[i for i in lines1 if i in lines2]
        for i in col3:
            if i in lines2:
                lines2.remove(i)
        for i in lines1:
            if i in col3 and suppress1!=1 and suppress2!=1 and suppress3!=1:
                sys.stdout.write(sp+sp+i)
            elif i in col3 and suppress1==1 and suppress2!=1 and suppress3!=1:
                sys.stdout.write(sp+i)
            elif i in col3 and suppress1!=1 and suppress2==1 and suppress3!=1:
                sys.stdout.write(sp+i)
            elif i in col3 and suppress1==1 and suppress2==1 and suppress3!=1:
                sys.stdout.write(i)
            elif i not in col3 and suppress1!=1:
                sys.stdout.write(i)
        for i in lines2:
            if suppress1!=1 and suppress2!=1:
                sys.stdout.write(sp+i)
            elif suppress1==1 and suppress2!=1:
                sys.stdout.write(i)
                                                                                                                                                                                                                                                                                                                    
if __name__ == "__main__":
    main()
