# Naive String Matching Algorithm
def naive_string_matching(text, pattern):
   n = len(text)
   m = len(pattern)
   indices = []  # Store starting indices of matches (first character)
 
   # Edge case: empty pattern matches at every position
   if m == 0:
       return list(range(n + 1))
   # Check every possible starting index in the text
   for i in range(n - m + 1):
       match = True
       for j in range(m):
           if text[i + j] != pattern[j]:
               match = False
               break
       if match:
           indices.append(i)  # Only the first character index
 
   return indices
 
# Main program
if __name__ == "__main__":
   text = input("Enter the text string (letters/numbers/symbols): ")
   pattern = input("Enter the pattern string: ")
 
   matches = naive_string_matching(text, pattern)
 
   if matches:
       print(f"Pattern found at starting indices (first character only): {matches}")
   else:
       print("Pattern not found in the text.")
