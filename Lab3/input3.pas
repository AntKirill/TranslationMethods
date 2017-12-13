program p;


const
  HELLO = 1;
  AM = 3;
  Kirill = 4;

var
  gg : integer;
var
  ui : double;

const
  IamHereAgain = 70;

var
  a, b, c : integer;

var
  i, j, k, n : integer;

begin
  gg := 10;
  i := 0;
  n := 3;
  ui := Kirill * 10 - I + 80;
  ui := (ui - 10) * (ui - 40) / (gg * (ui - ui / 2));
  read(gg);
  readln(a, b, c);
  readln();

  write(a, b, c);
  writeln(ui);

  for i := 0 to (2 + gg) do
  begin
    for j := 0 to n do
      for k := 0 to (i + j) do
        write(i);
  end;

  if (i = j) then
  begin
    write(i);
  end
  else
    write (j);

  while i < j do
  begin
    write(i);
    write(j);
    i := i + 1;
  end;

  for i := 0 to (2 + gg) do
  begin
    write(i);
    k := i + 1;
    write(k);
    a := k + 2;
    write(i, k, a);
  end;

  for i := (2 + gg) downto 0 do
  begin
    write(i);
    k := i + 1;
    write(k);
    a := k + 2;
    write(i, k, a);
  end;

  writeln();

  for i := (1 + gg) to (2 + gg) do
    writeln(i);

end.