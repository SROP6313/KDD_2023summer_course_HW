def cumulate(x):
  result = 1
  for i in range(1, x+1):
    result  = result * i

  return result

if __name__ == "__main__":
  print("modules.py is mainly running")