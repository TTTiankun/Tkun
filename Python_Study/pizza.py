def make_pizza(size, *toppings):
    """打印顾客点的所有配料"""
    print('\nMaking a ' + str(size) + '-inch pizza with the following toppings:')
    for topping in toppings:
        print('- ' + topping)

def build_profile(first, last, **user_info):
    """创建一个字典，其中包含我们知道的有关用户的一切"""
    profile = {}
    profile['first_name'] = first
    profile['last_name'] = last 
    for key, value in user_info.items():
        profile[key] = value
    return profile
