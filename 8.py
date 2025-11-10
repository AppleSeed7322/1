# Function to solve Fractional Knapsack Problem
def fractional_knapsack(capacity, parcels):
   # Calculate profit per weight for each parcel
   for parcel in parcels:
       parcel['profit_per_weight'] = parcel['profit'] / parcel['weight']
 
   # Sort parcels by profit/weight ratio in descending order
   parcels.sort(key=lambda x: x['profit_per_weight'], reverse=True)
 
   total_profit = 0
   items_taken = []
 
   for parcel in parcels:
       if capacity == 0:
           break
 
       if parcel['weight'] <= capacity:
           # Take the whole parcel
           items_taken.append({'weight': parcel['weight'], 'profit': parcel['profit'], 'fraction': 1})
           total_profit += parcel['profit']
           capacity -= parcel['weight']
       else:
           # Take fractional part of the parcel
           fraction = capacity / parcel['weight']
           items_taken.append({'weight': capacity, 'profit': parcel['profit'] * fraction, 'fraction': fraction})
           total_profit += parcel['profit'] * fraction
           capacity = 0  # Truck is full
 
   return total_profit, items_taken
 
# Main program
if __name__ == "__main__":
   parcels = []
 
   n = int(input("Enter the number of parcels: "))
 
   for i in range(n):
       weight = float(input(f"Enter weight of parcel {i+1}: "))
       profit = float(input(f"Enter profit of parcel {i+1}: "))
       parcels.append({'weight': weight, 'profit': profit})
 
   capacity = float(input("\nEnter maximum weight capacity of the truck: "))
 
   max_profit, taken = fractional_knapsack(capacity, parcels)
 
   # Display results in table format
   print(f"\nMaximum profit achievable: {max_profit:.2f}\n")
   print(f"{'Parcel':<10}{'Weight Taken':<15}{'Profit':<10}{'Fraction':<10}")
   print("-" * 45)
   for idx, item in enumerate(taken, start=1):
       print(f"{idx:<10}{item['weight']:<15.2f}{item['profit']:<10.2f}{item['fraction']:<10.2f}")
