let styles: ToDoInputStyles.definition = [%raw {| require("./ToDoInput.scss") |}]
type state = {
    text: string,
};

type action = ChangeText(string);

let component = ReasonReact.reducerComponent("ToDoInput");

let make = (
    ~submit: ToDoTypes.todo => unit, 
    ~text="", 
    ~newTodo=false, 
    ~placeholder="", 
    _children
) => {
    ...component,
    initialState: () => {
        text: text,
    },

    reducer: (action: action, _state: state) => {
        switch(action) {
        | ChangeText(text) => ReasonReact.Update({ text: text} )
        }
    },

    render: self => {
        let handleSubmit = (event:ReactEvent.Keyboard.t) => {
            if (ReactEvent.Keyboard.keyCode(event) == 13 /* Enter */) {
                submit({
                    id: -1,
                    content: self.state.text,
                    completed: false,
                })
                self.send(ChangeText(""));
            }
        };

        let onChange = event => {
            self.send(ChangeText(ReactEvent.Form.target(event)##value));
        };

        <input type_="text" 
            className=Cn.make([
                styles##textbox,
                styles##newTodo->Cn.ifTrue(newTodo),
            ])
            value=self.state.text
            onKeyDown={event => handleSubmit(event)}
            onChange
            placeholder
        />
    }
}
