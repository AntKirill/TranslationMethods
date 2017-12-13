grammar PascalGrammar;

@header {
    import java.lang.StringBuilder;
    import utils.*;
}

codeStructure returns [String str] : programHeader (declarationPart)? (functionsPart)? mainPart
{
    $str = $programHeader.str;
    $str += "\n" + $declarationPart.str;
    $str += $functionsPart.str;
    $str += "\n" + $mainPart.str;
};

functionsPart returns [String str] : {$str = "";};

declarationPart returns [String str] @init{$str = "";} : (varDeclaration
{
    $str += $varDeclaration.str;
}
|
constDeclaration
{
    $str += $constDeclaration.str;
}
)* ;

varDeclaration returns [String str] @init{$str = "";} : VAR (varDeclarationLine
{
    $str += $varDeclarationLine.str;
})+ ;

varDeclarationLine returns [String str] @init {$str = "";} : names_enumeration COLON type SEMI
{
    $str += $type.str + " " + $names_enumeration.str + ";\n";
    utils.Utils.addVars($type.str, $names_enumeration.str.split(", "));
};

names_enumeration returns [String str] @init {$str = "";} : identifier {$str += $identifier.text.toLowerCase();}
(COMMA identifier {$str += ", " + $identifier.text.toLowerCase();} )* | QUOTE string QUOTE {$str = "\"" + $string.str + "\"";} | ;

string returns [String str] @init {$str = "";} : identifier | ;

constDeclaration returns [String str] @init{$str = "";} : CONST (constDeclarationLine
{
    $str += $constDeclarationLine.str + "\n";
})+;

constDeclarationLine returns [String str] @init{$str = "";} : identifier EQUALITY number SEMI
{
    $str = "const int " + $identifier.text.toLowerCase() + " = " + $number.text + ";";
    utils.Utils.addVars("int", $identifier.text);
};

type returns [String str]:
CHAR {$str = "char";} | BOOLEAN {$str = "bool";} | INTEGER {$str = "int";} | DOUBLE {$str = "double";} | STRING {$str = "char *";};

typeDeclaration returns [String str] @init{$str = "";} : ;

programHeader returns [String str] : PROGRAM IDENTIFIER {$str = "#include<stdio.h>\n";} SEMI;

functionBody returns [String str] @init{$str = "";}: (statement {$str += "\t" + $statement.str + "\n";})* ;

statement returns [String str] @init{$str = "";} :
    assignment {$str = $assignment.str;} |
    functionInvoking {$str = $functionInvoking.str;} |
    loop {$str = $loop.str;} |
    ifstatement {$str = $ifstatement.str;} |
    whilestatement {$str = $whilestatement.str;};

loop 
    returns [String str]
    locals [String iterator = "", boolean down = false] @init{$str = "";} :
    FOR identifier {$str += "for (" + $identifier.text; $iterator = $identifier.text;}
    ASSIGNMENT rhsexpression {$str += " = " + $rhsexpression.str;}
    (TO {$down = false;}|DOWNTO{$down = true;}) rhsexpression {$str += "; " + $iterator ;
    if ($down) {
        $str += " >= " + $rhsexpression.str + "; " + $iterator;
        $str += "--)";
    }
    else {
        $str += " <= " + $rhsexpression.str + "; " + $iterator;
        $str += "++)";
    };
    }
    ((DO BEGIN {$str += "\n\t{\n\t";} functionBody {$str += $functionBody.str;} END SEMI {$str += "\t}";}) |
    (DO {$str += "\n\t{\n\t\t";} statement {$str += $statement.str;} {$str += "\n\t}";})) ;

ifstatement returns [String str] @init{$str = "";} : IF LPAREN condition RPAREN THEN {$str = "if (" + $condition.str + ")"; }
((BEGIN {$str += "\n\t{\n\t";} functionBody {$str += $functionBody.str;} END (SEMI | {$str += "\t}";} (ELSE {$str += "\n\telse\n\t";} ((BEGIN {$str += "\n\t{\n\t";} functionBody {$str += $functionBody.str;} END SEMI {$str += "\t}";}) |
                                                                                      ( {$str += "\n\t{\n\t\t";} statement {$str += $statement.str;} {$str += "\n\t}";}))))) |
( {$str += "\n\t{\n\t\t";} statement {$str += $statement.str;} {$str += "\n\t}";} {$str += "\t}";} (ELSE {$str += "\n\telse\n\t";} ((BEGIN {$str += "\n\t{\n\t";} functionBody {$str += $functionBody.str;} END SEMI) |
                                                                                   ( {$str += "\n\t{\n\t\t";} statement {$str += $statement.str;} {$str += "\n\t}";})))));

whilestatement returns [String str] @init{$str = "";} : WHILE condition {$str += "while (" + $condition.str + ")";}
((DO BEGIN {$str += "\n\t{\n\t";} functionBody {$str += $functionBody.str;} END SEMI {$str += "\t}";}) |
(DO {$str += "\n\t{\n\t\t";} statement {$str += $statement.str;} {$str += "\n\t}";})) ;


condition returns [String str] @init{$str = "";} :
rhsexpression
{
    $str += $rhsexpression.str;
}
conditionalSign
{
    $str += " "+$conditionalSign.text + " ";
}
rhsexpression
{
    $str += $rhsexpression.str;
}
;

conditionalSign : (LESS | NOTLESS | EQUALITY | NOTEQUALITY | NOTMORE | BIGGER) ;

functionInvoking returns [String str] @init{$str = "";} : functionName LPAREN names_enumeration RPAREN SEMI
{
    if (($functionName.str).equals("scanf") || ($functionName.str).equals("scanfln")) {
        if ($names_enumeration.str.equals("")) {
          $str = "getchar();";
        } else if (($functionName.str).equals("scanf")) {
          $str = utils.Utils.genScanf(false, $names_enumeration.str.split(", "));
        } else {
          $str = utils.Utils.genScanf(true, $names_enumeration.str.split(", "));
        }
    } else if (($functionName.str).equals("printf") || ($functionName.str).equals("printfln")) {
        if ($names_enumeration.str.equals("")) {
            $str = "printf(\"\\n\");";
        } else if (($functionName.str).equals("printf")) {
            $str = utils.Utils.genPrintf(false, $names_enumeration.str.split(", "));
        } else {
            $str = utils.Utils.genPrintf(true, $names_enumeration.str.split(", "));
        }
    } else {
        $str = $functionName.str + "(" + $names_enumeration.str + ");";
    }
};

functionName returns [String str] @init{$str = "";} : READ {$str = "scanf";} | READLN {$str = "scanfln";} |
WRITE {$str = "printf";} | WRITELN {$str = "printfln";};

assignment returns [String str] @init{$str = "";} : identifier ASSIGNMENT rhsexpression SEMI
{
    $str = $identifier.text.toLowerCase() + " = " + $rhsexpression.str + ";";
};

rhsexpression returns [String str] @init{$str = "";} : identifier {$str = $identifier.text.toLowerCase();} | number {$str = $number.text;} |
(LPAREN {$str += "(";})*(number {$str += $number.text;} | identifier {$str += $identifier.text.toLowerCase();}) (RPAREN {$str += ")";})*
((PLUS {$str += " + ";} | MINUS {$str += " - ";} | MUL {$str += " * ";} | DIV {$str += " / ";} )
(LPAREN {$str += "(";})*(number {$str += $number.text;} | identifier {$str += $identifier.text.toLowerCase();}) (RPAREN {$str += ")";})*
)* ;

mainPart returns [String str] : BEGIN functionBody END
{
    $str = "int main()\n{\n";
    $str += $functionBody.str;
    $str += "\treturn 0;\n";
    $str += "}";
};

identifier : IDENTIFIER;

number : NUMBER;

SEMI
   : ';'
   ;

THEN : T H E N ;

ELSE : E L S E ;

COLON
   : ':'
   ;

COMMA
   : ','
   ;

DOT
   : '.'
   ;

QUOTE
: '\''
;

LPAREN
   : '('
   ;


RPAREN
   : ')'
   ;

EQUALITY
   : '='
   ;

NOTEQUALITY : '<>' ;

ASSIGNMENT
   : ':='
   ;

PLUS
   : '+'
   ;

MINUS
   : '-'
   ;

MUL
   : '*'
   ;

DIV
   : '/'
   ;

NOTMORE : '<=' ;
NOTLESS : '>=' ;
LESS : '<' ;
BIGGER : '>' ;

IF : I F ;

PROGRAM
   : P R O G R A M
   ;

VAR
   : V A R
   ;

BEGIN
   : B E G I N
   ;

END
   : E N D
   ;

CONST
   : C O N S T
   ;

BOOLEAN
   : B O O L E A N
   ;

CHAR
   : C H A R
   ;

INTEGER
   : I N T E G E R
   ;

REAL
   : R E A L
   ;

DOUBLE
   : D O U B L E
   ;

EXTENDED
   : E X T E N D E D
   ;

STRING
   : S T R I N G
   ;

READ
   : R E A D
   ;

READLN
   : R E A D L N
   ;

WRITE
   : W R I T E
   ;

WRITELN
   : W R I T E L N
   ;

FOR : F O R ;

TO : T O ;

DOWNTO : D O W N T O ;

WHILE : W H I L E ;

DO : D O ;

IDENTIFIER
   : ('a' .. 'z' | 'A' .. 'Z') ('a' .. 'z' | 'A' .. 'Z' | '0' .. '9' | '_')*
   ;

NUMBER
   : ('0' .. '9')+
   ;

fragment A
   : ('a' | 'A')
   ;

fragment B
   : ('b' | 'B')
   ;

fragment C
   : ('c' | 'C')
   ;

fragment D
   : ('d' | 'D')
   ;

fragment E
   : ('e' | 'E')
   ;

fragment F
   : ('f' | 'F')
   ;

fragment G
   : ('g' | 'G')
   ;

fragment H
   : ('h' | 'H')
   ;

fragment I
   : ('i' | 'I')
   ;

fragment J
   : ('j' | 'J')
   ;

fragment K
   : ('k' | 'K')
   ;

fragment L
   : ('l' | 'L')
   ;

fragment M
   : ('m' | 'M')
   ;

fragment N
   : ('n' | 'N')
   ;

fragment O
   : ('o' | 'O')
   ;

fragment P
   : ('p' | 'P')
   ;

fragment Q
   : ('q' | 'Q')
   ;

fragment R
   : ('r' | 'R')
   ;

fragment S
   : ('s' | 'S')
   ;

fragment T
   : ('t' | 'T')
   ;

fragment U
   : ('u' | 'U')
   ;

fragment V
   : ('v' | 'V')
   ;

fragment W
   : ('w' | 'W')
   ;

fragment X
   : ('x' | 'X')
   ;

fragment Y
   : ('y' | 'Y')
   ;

fragment Z
   : ('z' | 'Z')
   ;

WS
   : [ \t\r\n]+ -> skip
   ;

OLD_STYLE_COMMENT
   : '(*' .*? '*)' -> skip
   ;

COMMENT
   : '{' .*? '}' -> skip
   ;
