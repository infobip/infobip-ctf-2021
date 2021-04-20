# Solution

Math algebra that converts each char to a base64 encoded string and the `==` sign is extracted and put in front of the parenthesis.

The logic behind it is that an element that is in front of the parenthesis can be expanded to join each element:
```
==*(Vw+aA) -> Vw==+aA==
```

The `==` is kind of a revealing sign that we are using base64, so after decode you would have:
```
Vw==+aA== -> W+h -> Wh
```

The solution is to apply the formula for each element and decode elements to get the text:
```python
>>> elements = formula[4:-1].split('+')
>>> from base64 import b64decode
>>> elements[0]
'Vw'
>>> ''.join([b64decode(i + "==").decode() for i in elements])
"What kind of mathematics is this? Let's call it: the base64 algebra. Never gonna give you up, never gonna let you down. 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 0 = 0 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1. Weird ways of algebra. More text, text, more text and more text. Let's give it a few more bytes. More? A bit more ... and a bit more. This should be enough :) Well, changed my mind. Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Sed ut perspiciatis, unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam eaque ipsa, quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt, explicabo. Nemo enim ipsam voluptatem, quia voluptas sit, aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos, qui ratione voluptatem sequi nesciunt, neque porro quisquam est, qui dolorem ipsum, quia dolor sit amet consectetur adipisci[ng]velit, sed quia non numquam [do] eius modi tempora inci[di]dunt, ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum[d] exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Congratulations. The flag is ibctf{wh4t-k1nd_0f_4lg3br4-iz-diz}. Quis autem vel eum iure reprehenderit, qui in ea voluptate velit esse, quam nihil molestiae consequatur, vel illum, qui dolorem eum fugiat, quo voluptas nulla pariatur? [33] At vero eos et accusamus et iusto odio dignissimos ducimus, qui blanditiis praesentium voluptatum deleniti atque corrupti, quos dolores et quas molestias excepturi sint, obcaecati cupiditate non provident, similique sunt in culpa, qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio. Nam libero tempore, cum soluta nobis est eligendi optio, cumque nihil impedit, quo minus id, quod maxime placeat, facere possimus, omnis voluptas assumenda est, omnis dolor repellendus. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet, ut et voluptates repudiandae sint et molestiae non recusandae. Itaque earum rerum hic tenetur a sapiente delectus, ut aut reiciendis voluptatibus maiores alias consequatur aut perferendis doloribus asperiores repellat"
```
