let styles: AppStyles.definition = [%raw {| require("./App.css") |}]
let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
    ...component,

    render: _self => {
        <div className=styles##test>
            { ReasonReact.string("App") }
        </div>
    }
}
