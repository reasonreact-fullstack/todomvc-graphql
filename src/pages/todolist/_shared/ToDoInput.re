let styles: ToDoInputStyles.definition = [%raw {| require("./ToDoInput.scss") |}]
type state = {
    givenText: string,
    currentText: string,
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
        givenText: text,
        currentText: text,
    },

    reducer: (action: action, state: state) => {
        switch(action) {
        | ChangeText(text) => ReasonReact.Update({ ...state, currentText: text} )
        }
    },

    render: self => {
        let handleSubmit = (event:ReactEvent.Keyboard.t) => {
            let keyCode = ReactEvent.Keyboard.keyCode(event);
            switch(keyCode) {
            | 13 /* Enter */ => {
                submit({
                    id: -1,
                    content: self.state.currentText,
                    completed: false,
                })
                self.send(ChangeText(""));
            }
            | 27 /* ESC */ => {
                self.send(ChangeText(self.state.givenText))
            }
            | _ => ()
            }
        };

        let onChange = event => {
            self.send(ChangeText(ReactEvent.Form.target(event)##value));
        };

        <input type_="text" 
            className=Cn.make([
                styles##textbox,
                styles##newMode->Cn.ifTrue(newTodo),
                styles##editMode->Cn.ifTrue(!newTodo),
            ])
            value=self.state.currentText
            onKeyDown={event => handleSubmit(event)}
            onChange
            placeholder
            autoFocus=true
        />
    }
}
